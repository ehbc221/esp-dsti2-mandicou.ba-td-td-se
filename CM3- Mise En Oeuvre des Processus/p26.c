#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
int main()
{
	pid_t pid = 0;
	int status;
	pid=fork();
	switch (pid)
	{
		case -1:
			perror ("Error dans l'appel fork");
			exit(1);
		case 0: /*le fils */
			printf("Processus fils %d, mon pere est %d\n", getpid(), getppid() );
			exit(2);
		default : /* Le pere */
			printf("Pere %d : a cree processus %d\n", getpid(), pid);
			wait (&status);
			if (WIFEXITED (status))
				printf("Le fils termine normalement: status = %d\n", WEXITSTATUS (status));
			else
				printf("Fils termine anormalement\n");
	}
}