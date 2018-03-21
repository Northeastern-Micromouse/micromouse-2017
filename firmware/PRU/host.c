#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int writePRU(int fd, int steps, int us) {
	unsigned char data[] = {(unsigned char)steps & 0xFF, 
							(unsigned char)((steps & 0x0000FF00) >> 8),
							(unsigned char)((steps & 0x00FF0000) >> 16),
							(unsigned char)((steps & 0xFF000000) >> 24),
							(unsigned char)((us & 0x000000FF)),
							(unsigned char)((us & 0x0000FF00) >> 8),
							(unsigned char)((us & 0x00FF0000) >> 16),
							(unsigned char)((us & 0xFF000000) >> 24) };
	return write(fd, data, 8);
}

int main() {
	
	
	
	int pru0_file = open("/dev/rpmsg_pru30", O_RDWR);
    if (pru0_file < 0) {
		printf("Error opening file.\n");
        return pru0_file;
	}
	
	writePRU(pru0_file, 1000, 1000);
	
	return 0;
}

