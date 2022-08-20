/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbousque <tbousque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 00:16:29 by tbousque          #+#    #+#             */
/*   Updated: 2022/08/20 17:33:13 by tbousque         ###   ########.fr       */
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

int	ft_isnumber(char const *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

int	check_arg_error(int argc, char const *argv[])
{
	if (argc < 3)
		write(STDERR_FILENO, "Error: Not enough args.\n", 24);
	else if (argc > 3)
		write(STDERR_FILENO, "Error: Too much args.\n", 22);
	if (argc != 3)
		return (1);
	if (!ft_isnumber(argv[1]) || ft_atoi(argv[1]) <= 0)
	{
		write(STDERR_FILENO, "Error: PID is invalid.\n", 23);
		return (1);
	}
	return (0);
}

int	main(int argc, char const *argv[])
{
	struct sigaction	myaction;

	if (check_arg_error(argc, argv))
		return (EXIT_FAILURE);
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
	write(STDERR_FILENO, \
		"No response from the server, PID might be invalid.\n", 51);
	return (EXIT_FAILURE);
}
