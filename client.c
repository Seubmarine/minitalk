# include "minitalk.h"

// char *str_minitalk = NULL;

void sendraw(pid_t server_pid, int data)
{
	if (data)
		kill(server_pid, SIGUSR2);
	else
		kill(server_pid, SIGUSR1);
	printf("%i", data);
}

void	send_pid(pid_t server_pid, pid_t client_pid)
{
	int i;
	int	current;

	i = sizeof(client_pid) * 8 - 1;
	while (i >= 0)
	{
		current = (client_pid >> i & 1);
		sendraw(server_pid, current);
		usleep(300);
		i--;
	}
	printf("\n");
}

int main(int argc, char const *argv[])
{
	pid_t server_pid;
	pid_t client_pid;
	if (argc < 3)
	{
		printf("Not enough args");
		return (0);
	}
	server_pid = atoi(argv[1]);
	client_pid = getpid();
	printf("client pid: %i\n", client_pid);
	send_pid(server_pid, client_pid);
	return 0;
}
