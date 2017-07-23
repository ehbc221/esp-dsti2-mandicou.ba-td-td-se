#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
int main()
{
	pid_t status;
	status=fork();
	switch (status)
	{
		case -1:
			perror("Error creation de processus");
			return 1;
		case 0: // Code du Fils
			switch(fork())
			{
				case -1:
					perror("Creation de processus intermediaire");
					return 1;
				case 0:
					printf("Processus %d, Mon Pere: %d\n", getpid(), getppid());
					break;
				default :
					return 0;
			}
			break;
		default :
			wait(&status);
			break;
	}
	exit(EXIT_SUCCESS);
}