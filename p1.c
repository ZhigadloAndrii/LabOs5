#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(){
	char string[] = "Текст з процесу 1";
	char cmd[100];
	sprintf(cmd, "sudo ./p2 %d %lx %lu\n", getpid(), (long unsigned int) string, strlen(string) + 1);
	system(cmd);

	printf("(p1)Нажміть Enter для продовження \n");
	getchar();

	printf("(p1)Текст став: %s\n", string);

	return 0;
}
