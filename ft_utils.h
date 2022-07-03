/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbousque <tbousque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 02:08:49 by tbousque          #+#    #+#             */
/*   Updated: 2022/07/03 02:20:04 by tbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
# define FT_UTILS_H
# include <stddef.h>
# include <unistd.h>

int		ft_atoi(const char *nptr);
void	*ft_memset(void *s, int c, size_t n);
void	ft_putnbr_fd(int n, int fd);
void	*ft_memcpy(void *dest, const void *src, size_t n);
#endif
