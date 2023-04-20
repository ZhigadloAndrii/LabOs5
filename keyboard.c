#include <linux/input.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	if(argc < 2){
		printf("Usage: %s <device\n>", argv[0]);
		return 1;
	}

	const char *dev = argv[1];
	int fd = open(dev, O_RDONLY);
	if (fd == -1){
		perror("open");
		return 1;
	}

	struct input_event ev;

	while(1)
	{
		int bytes = read(fd, &ev, sizeof(ev));
		if(bytes == -1){
			perror("read");
			return 1;
		}
		if (bytes != sizeof(ev)){
			continue;
		}
		if (ev.type == EV_KEY && ev.value == 0){
			printf("key %d pressed\n", ev.code);
		}
		if (ev.type == EV_KEY && ev.value == 1){
			printf("key %d released\n", ev.code);
		}
	}
}
