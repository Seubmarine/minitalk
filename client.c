/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbousque <tbousque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 00:16:29 by tbousque          #+#    #+#             */
/*   Updated: 2022/07/03 00:19:51 by tbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_signal(pid_t server_pid, int data)
{
	if (data)
		kill(server_pid, SIGUSR2);
	else
		kill(server_pid, SIGUSR1);
}

void	send_pid(pid_t server_pid, pid_t client_pid)
{
	int	i;
	int	current;

	i = sizeof(client_pid) * 8 - 1;
	while (i >= 0)
	{
		current = (client_pid >> i & 1);
		send_signal(server_pid, current);
		usleep(10000);
		i--;
	}
}

typedef struct s_server_info
{
	pid_t		pid;
	const char	*str;
}	t_server_info;

t_server_info	g_server;

void	send_string(int signum)
{
	static size_t	i = 0;
	static size_t	bit_i = 0;
	char			current;

	(void) signum;
	current = g_server.str[i] >> bit_i & 1;
	bit_i++;
	if (bit_i == 8)
	{
		bit_i = 0;
		i++;
		if (g_server.str[i - 1] == '\0')
		{	
			send_signal(g_server.pid, current);
			exit(EXIT_SUCCESS);
		}
	}
	send_signal(g_server.pid, current);
}

void	exit_client(int signum)
{
	(void) signum;
	exit(EXIT_SUCCESS);
}

int	main(int argc, char const *argv[])
{
	pid_t	client_pid;

	signal(SIGUSR2, send_string);
	signal(SIGUSR1, exit_client);
	if (argc < 3)
	{
		printf("Not enough args");
		return (0);
	}
	g_server.pid = atoi(argv[1]);
	client_pid = getpid();
	printf("client pid: %i\n", client_pid);
	g_server.str = argv[2];
	send_pid(g_server.pid, client_pid);
	while (1)
		;
	return (EXIT_FAILURE);
}
