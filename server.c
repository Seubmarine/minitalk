# include "minitalk.h"
# include "vector.h"

void printsignum(int signum)
{
	printf("signum = %i\n", signum);
}

void	exit_server(int signum)
{
	printsignum(signum);
	exit(EXIT_SUCCESS);
}

pid_t	client_pid;

char	bit_to_byte(char bits[8])
{
	int i;
	char byte = 0;
 
	i = 7;
	while (i >= 0)
	{
		byte = byte << 1;
		byte += bits[i];
		i--;
	}
	return (byte);
}

void get_client_pid(int signum);

void	print_bits(char bits[8])
{
	for (size_t i = 0; i < 8; i++)
	{
		printf("%i", (int) bits[i]);
	}
	printf("\n");
}
int ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

void receive_string(int signum)
{
	static char			bits[8] = {0};
	static t_vec	vec = {.data = NULL, .capacity = 0, .len = 0};
	static size_t			bits_i = 0;
	
	printf("received a signal\n");
	(void) signum;
	if (vec.data == NULL)
		vec = vec_new(4);
	if (signum == SIGUSR2) // 1
		bits[bits_i] = 1;
	else if (signum == SIGUSR1) // 0
		bits[bits_i] = 0;
	bits_i++;
	if (bits_i == 8)
	{
		print_bits(bits);
		bits_i = 0;
		printf("bits:%c\n", bit_to_byte(bits));
		vec_push_back(&vec, bit_to_byte(bits));
		memset(bits, 0, 8);
		if (vec.data[vec.len - 1] == '\0')
		{
			//printf("%s\n\n", vec.data);
			printf("strlen: %i, veclen: %lu\n", ft_strlen(vec.data), vec.len);
			write(1, vec.data, vec.len - 1);
			vec_free(&vec);
			signal(SIGUSR1, get_client_pid);
			signal(SIGUSR2, get_client_pid);
			return ;
		}
	}
	printf("Send signal to client: %i\n", client_pid);
	kill(client_pid, SIGUSR2); // say to continue to send
}


void get_client_pid(int signum)
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
		printf("client pid: %i\n", current_int);
		client_pid = current_int;
		current_int = 0;
		count = 0;
		signal(SIGUSR1, receive_string);
		signal(SIGUSR2, receive_string);
		printf("set new signal to %i\n", client_pid);
		kill(client_pid, SIGUSR2);
		printf("kill client\n");
	}
}

int main(int argc, char const *argv[])
{
	pid_t	server_pid;

	(void) argc;
	(void) argv;
	server_pid = getpid();
	printf("server pid: %i\n", server_pid);
	//signal(SIGINT, exit_server);
	signal(SIGUSR1, get_client_pid);
	signal(SIGUSR2, get_client_pid);
	while (1);
	return (EXIT_FAILURE);
}
