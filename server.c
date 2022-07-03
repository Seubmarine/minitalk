/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbousque <tbousque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 00:16:19 by tbousque          #+#    #+#             */
/*   Updated: 2022/07/03 02:10:44 by tbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

pid_t	g_client_pid;

char	bit_to_byte(char bits[8])
{
	int		i;
	char	byte;

	byte = 0;
	i = 7;
	while (i >= 0)
	{
		byte = byte << 1;
		byte += bits[i];
		i--;
	}
	return (byte);
}

void	get_client_pid(int signum);

void	receive_string(int signum)
{
	static char		bits[8] = {0};
	static t_vec	vec = {.data = NULL, .capacity = 0, .len = 0};
	static size_t	bits_i = 0;

	(void) signum;
	if (vec.data == NULL)
		vec = vec_new(4);
	bits[bits_i] = 1;
	if (signum == SIGUSR1)
		bits[bits_i] = 0;
	if (++bits_i == 8)
	{
		bits_i = 0;
		vec_push_back(&vec, bit_to_byte(bits));
		if (vec.data[vec.len - 1] == '\0')
		{
			vec.data[vec.len - 1] = '\n';
			write(1, vec.data, vec.len);
			vec_free(&vec);
			signal(SIGUSR1, get_client_pid);
			signal(SIGUSR2, get_client_pid);
			return ;
		}
	}
	kill(g_client_pid, SIGUSR2);
}

void	get_client_pid(int signum)
{
	static int	count = 0;
	static int	current_int = 0;

	current_int = current_int << 1;
	if (signum == SIGUSR2)
		current_int += 1;
	count++;
	if (count == (sizeof(pid_t) * 8))
	{
		g_client_pid = current_int;
		current_int = 0;
		count = 0;
		signal(SIGUSR1, receive_string);
		signal(SIGUSR2, receive_string);
		kill(g_client_pid, SIGUSR2);
	}
}

int	main(int argc, char const *argv[])
{
	pid_t	server_pid;

	(void) argc;
	(void) argv;
	server_pid = getpid();
	write(1, "server pid: ", 12);
	ft_putnbr_fd(server_pid, 1);
	write(1, "\n", 1);
	signal(SIGUSR1, get_client_pid);
	signal(SIGUSR2, get_client_pid);
	while (1)
		;
	return (EXIT_FAILURE);
}
