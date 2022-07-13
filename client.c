/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbousque <tbousque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 00:16:29 by tbousque          #+#    #+#             */
/*   Updated: 2022/07/13 02:14:54 by tbousque         ###   ########.fr       */
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

t_server_info	g_server;

void	send_string(int signum)
{
	static size_t	i = 0;
	static size_t	bit_i = 0;
	char			current;

	(void) signum;
	g_server.has_response = true;
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
	signal(SIGUSR2, send_string);
	signal(SIGUSR1, exit_client);
	if (argc < 3)
	{
		write(1, "Not enough args\n", 16);
		return (0);
	}
	g_server.pid = ft_atoi(argv[1]);
	g_server.str = argv[2];
	g_server.has_response = false;
	kill(g_server.pid, SIGUSR1);
	sleep(3);
	if (g_server.has_response)
	{
		while (1)
			pause();
	}
	write(1, "No response from the server, server PID might be invalid\n", 57);
	return (EXIT_FAILURE);
}
