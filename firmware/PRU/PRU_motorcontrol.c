#include <stdint.h>
#include <pru_cfg.h>
#include <pru_intc.h>
#include <pru_rpmsg.h>
#include "resource_table.h"

#define VIRTIO_CONFIG_S_DRIVER_OK 4

#define MM_MOTOR_LEFT (1 << 0)
#define MM_MOTOR_RIGHT (1 << 1)

volatile register uint32_t __R30;
volatile register uint32_t __R31;

unsigned char payload[RPMSG_BUF_SIZE];

void main(void)
{
	struct pru_rpmsg_transport transport;
	unsigned short src, dst, len;
	volatile unsigned char* status;
		
	/* Clear SYSCFG[STANDBY_INIT] to enable OCP master port */
	CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;	
	CT_INTC.SICR_bit.STS_CLR_IDX = FROM_ARM_HOST;
	
	status = &resourceTable.rpmsg_vdev.status;
	while(!(*status & VIRTIO_CONFIG_S_DRIVER_OK));
	
	pru_rpmsg_init(&transport, &resourceTable.rpmsg_vring0, &resourceTable.rpmsg_vring1, TO_ARM_HOST, FROM_ARM_HOST);
	while (pru_rpmsg_channel(RPMSG_NS_CREATE, &transport, CHAN_NAME, CHAN_DESC, CHAN_PORT) != PRU_RPMSG_SUCCESS);
	
	for(;;) {
		if(__R31 & HOST_INT) {
			if (pru_rpmsg_receive(&transport, &src, &dst, payload, &len) == PRU_RPMSG_SUCCESS) {
				
				uint32_t stepsLeft = payload[0] | 
									(payload[1] << 8) | 
									(payload[2] << 16) | 
									(payload[3] << 24);
				uint32_t usLeft = payload[4] | 
									(payload[5] << 8) | 
									(payload[6] << 16) | 
									(payload[7] << 24);
				uint32_t stepsRight = payload[8] | 
									(payload[9] << 8) | 
									(payload[10] << 16) | 
									(payload[11] << 24);
				uint32_t usRight = payload[12] | 
									(payload[13] << 8) | 
									(payload[14] << 16) | 
									(payload[15] << 24);
				
				// Since steps represents number of desired falling edges,
				// multiply by 2 so that we can decrement on both edges
				stepsLeft *= 2;
				stepsRight *= 2;
				
				int leftCounter = usLeft;
				int rightCounter = usRight;
				
				// While there are remaining steps, loop every half microsecond
				// If it's time to toggle, do so. Otherwise decrement the 
				// counter and continue
				while(stepsLeft && stepsRight) {
					if(stepsLeft && !leftCounter) {
						__R30 ^= MM_MOTOR_LEFT;
						stepsLeft--;
						leftCounter = usLeft;
					}
					if(stepsRight && !rightCounter) {
						__R30 ^= MM_MOTOR_RIGHT;
						stepsRight--;
						rightCounter = usRight;
					}
					
					leftCounter--;
					rightCounter--;
					__delay_cycles(100);
				}
				
				// Report all done to the host
				pru_rpmsg_send(&transport,dst, src, "K", 1);
			}
			else {
				CT_INTC.SICR_bit.STS_CLR_IDX = FROM_ARM_HOST;
			}
		}
	}
}

