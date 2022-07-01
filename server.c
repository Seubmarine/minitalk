#include "minitalk.h"

char *str_minitalk = NULL;
void printsignum(int signum)
{
	printf("signum = %i\n", signum);
}

void	end(int signum)
{
	printsignum(signum);
	exit(EXIT_SUCCESS);
}

void print(int signum)
{
	static int count = 0;
	static int current_int = 0;

	current_int = current_int << 1;
	if (signum == SIGUSR1)
		printf("0");
	else if (signum == SIGUSR2)
	{
		current_int += 1;
		printf("1");
	}
	count++;
	if (count == (sizeof(pid_t) * 8))
	{
		printf("\ncurrent pid = %i\n", current_int);
		current_int = 0;
		count = 0;
	}
}

int main(int argc, char const *argv[])
{
	pid_t	server_pid;

	(void) argc;
	(void) argv;
	server_pid = getpid();
	printf("server pid = %i\n", server_pid);
	signal(SIGINT, end);
	signal(SIGUSR1, print);
	signal(SIGUSR2, print);
	while (1);
	return (EXIT_FAILURE);
}
