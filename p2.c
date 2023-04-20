#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>

int main(int argc, char* argv[]){

	if (argc != 4){
		printf("ERROR");
		exit(1);
	}

	int pid = atoi(argv[1]);
	unsigned long addr = strtoul(argv[2], NULL, 16);
	int len = atoi(argv[3]);

	char proc_mem[100];
	sprintf(proc_mem, "/proc/%d/mem", pid);

	printf("(p2)Відкриваємо %s, адреса - %ld\n", proc_mem, addr);

	int fd_proc_mem = open(proc_mem, O_RDWR);
	if (fd_proc_mem == -1){
		printf("(p2)Помилка відкриття %s\n", proc_mem);
		exit(1);
	}

	char* buf = malloc(len);
	if (buf == NULL){
		printf("(p2)Помилка читання\n");
		exit(1);
	}

	lseek(fd_proc_mem, addr, SEEK_SET);
	if (read(fd_proc_mem, buf, len) == -1){
		printf("(p2)Помилка читання з %ld\n", addr);
		exit(1);
	}

	printf("(p2)Текст з %ld %d -: \n", addr, pid);
	printf(" %s\n", buf);

	strncpy(buf, "(p2p2p2p2p2)", len);

	lseek(fd_proc_mem, addr, SEEK_SET);
	if(write(fd_proc_mem, buf, len) == -1){
		printf("Помилка при записі\n");
		exit(1);
	}

	free(buf);
	close(fd_proc_mem);

	return 0;
}

