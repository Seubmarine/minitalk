/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbousque <tbousque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 00:16:29 by tbousque          #+#    #+#             */
/*   Updated: 2022/07/17 05:15:02 by tbousque         ###   ########.fr       */
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

const char	*g_str;

void	send_string(int signum, siginfo_t *info, void *ucontext)
{
	static unsigned char	current_char[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	static size_t			bit_i = 0;

	(void) ucontext;
	(void) signum;
	if (bit_i == 0)
	{
		ft_memset(current_char, 2, 8);
		bit_i = 0;
		while (bit_i < 8)
		{
			current_char[bit_i] = *g_str >> bit_i & 1;
			bit_i++;
		}
		bit_i = 0;
		g_str++;
	}
	send_signal(info->si_pid, current_char[bit_i]);
	if (++bit_i == 8)
	{
		bit_i = 0;
		if (*(g_str - 1) == '\0')
			exit(EXIT_SUCCESS);
	}
}

int	main(int argc, char const *argv[])
{
	struct sigaction	myaction;

	if (argc < 3)
	{
		write(1, "Not enough args\n", 16);
		return (0);
	}
	g_str = argv[2];
	sigemptyset(&(myaction.sa_mask));
	myaction.sa_flags = SA_SIGINFO;
	myaction.sa_sigaction = send_string;
	sigaction(SIGUSR2, &myaction, NULL);
	kill(ft_atoi(argv[1]), SIGUSR1);
	sleep(3);
	if (g_str != argv[2])
	{
		while (1)
			pause();
	}
	write(1, "No response from the server, server PID might be invalid\n", 57);
	return (EXIT_FAILURE);
}
