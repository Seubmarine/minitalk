/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbousque <tbousque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 02:22:41 by tbousque          #+#    #+#             */
/*   Updated: 2022/07/13 02:12:31 by tbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# define _GNU_SOURCE //TO REMOVE
# include <unistd.h>
# include <stddef.h>
# include <signal.h>
# include <stdbool.h>
# include "ft_utils.h"
# include "vector.h"

typedef struct s_server_info
{
	pid_t		pid;
	const char	*str;
	bool		has_response;
}	t_server_info;

#endif