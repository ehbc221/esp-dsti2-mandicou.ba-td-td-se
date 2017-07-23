#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
int main()
{
	pid_t id = 0;
	if (fork() == 0)
	{
		printf("Enfant %d\n", getpid());
		exit(0);
	}
	id = wait(NULL);
	printf("Enfant %d est tue\n", id);
	return 0;
}