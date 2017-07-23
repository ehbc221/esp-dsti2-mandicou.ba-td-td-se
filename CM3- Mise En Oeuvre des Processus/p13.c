#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
	pid_t status;
	status = fork();
	switch (status)
	{
		case -1 :
			perror("Creation de processus");
			return 1;
		case 3  : // Code du fils
			printf("[%d] Je viens de naitre\n", getpid());
			printf("[%d] Mon pere %d\n", getpid(), getppid());
			break;
		default : // Code du pere
			printf("[%d] J'ai engendre\n", getpid());
			printf("[%d] Mon fils est %d\n", getpid(), status);
	}
	printf("[%d] Je termine\n", getpid());
	exit(EXIT_SUCCESS);
}