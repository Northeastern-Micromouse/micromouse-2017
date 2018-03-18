PRU_RPMSG_ROOT:= /usr/lib/ti/pru-software-support-package/
PRU_INCLUDE:= --include_path=/usr/include/arm-linux-gnueabihf/ --include_path=/usr/share/ti/cgt-pru/include --include_path=$(PRU_RPMSG_ROOT)include/ --include_path=$(PRU_RPMSG_ROOT)include/am335x/
CODE_ROOT:=./
PRU0_ROOT:= $(CODE_ROOT)pru0
PRU1_ROOT:= $(CODE_ROOT)pru1
LINKER_CMD_FILE:= PRU_motorcontrol.cmd
PRU_TOOLS:=/usr/bin/

CFLAGS=-v3 -O2 --endian=little --hardware_mac=on

LDFLAGS+= -L.

am335x-pru0-fw: $(CODE_ROOT)PRU_motorcontrol.c
	$(PRU_TOOLS)clpru $(CFLAGS) $(PRU_INCLUDE) -ppd -ppa -fe $(PRU0_ROOT)/main0.object $(CODE_ROOT)PRU_motorcontrol.c -D PRU0
	$(PRU_TOOLS)clpru -z $(LINKER_CMD_FILE) -o $(PRU0_ROOT)/am335x-pru0-fw $(PRU0_ROOT)/main0.object -I/usr/share/ti/cgt-pru/lib -l$(PRU_RPMSG_ROOT)lib/rpmsg_lib.lib

am335x-pru1-fw: $(CODE_ROOT)PRU_motorcontrol.c
	$(PRU_TOOLS)clpru $(CFLAGS) $(PRU_INCLUDE) -ppd -ppa -fe $(PRU1_ROOT)/main1.object $(CODE_ROOT)PRU_motorcontrol.c -D PRU1
	$(PRU_TOOLS)clpru -z $(LINKER_CMD_FILE) -o $(PRU1_ROOT)/am335x-pru1-fw $(PRU1_ROOT)/main1.object -I/usr/share/ti/cgt-pru/lib -l$(PRU_RPMSG_ROOT)lib/rpmsg_lib.lib

install: am335x-pru0-fw am335x-pru1-fw
	cp $(PRU0_ROOT)/am335x-pru0-fw /lib/firmware
	cp $(PRU1_ROOT)/am335x-pru1-fw /lib/firmware
	rmmod -f pru_rproc
	modprobe pru_rproc

clean:
	rm $(PRU0_ROOT)/am335x-pru0-fw
	rm $(PRU1_ROOT)/am335x-pru1-fw
	rm $(PRU0_ROOT)/*.object
	rm $(PRU1_ROOT)/*.object
	rm *.pp

