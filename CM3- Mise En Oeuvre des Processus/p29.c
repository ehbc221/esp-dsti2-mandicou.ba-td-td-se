#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
int main(int argc, char const **argv[])
{
	switch (fork())
	{
		case -1:
			perror ("Error Creation de processus");
			return 1;
		case 0:
			printf("%d Pere : %d\n", getpid(), getppid());
			sleep (2);
			printf("%d Pere : %d\n", getpid(), getppid());
			exit (0);
		default :
			sleep (1);
			printf("%d fin du pere : \n", getpid());
			exit(0);
	}
	return 0;
}