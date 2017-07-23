#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
	printf("Avant fork\n");
	fork();
	printf("Apres fork\n");
	return 0;
}