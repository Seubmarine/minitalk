/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbousque <tbousque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 02:09:28 by tbousque          #+#    #+#             */
/*   Updated: 2022/07/03 02:21:03 by tbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"

static int	ft_isspace(int c)
{
	return (c == ' ' || c == '\f' || \
		c == '\n' || c == '\r' || c == '\t' || c == '\v');
}

int	ft_atoi(const char *nptr)
{
	int	number;
	int	sign;

	sign = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	number = 0;
	while (*nptr && *nptr >= '0' && *nptr <= '9')
		number = (number * 10) + (*nptr++ - 48);
	number *= sign;
	if (sign == 1 && number < 0)
		return (-1);
	else if (sign == -1 && number > 0)
		return (0);
	return (number);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*s_casted;

	s_casted = s;
	while (n--)
		*s_casted++ = c;
	return (s);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	d = dest;
	s = src;
	if (dest == NULL && src == NULL)
		return (dest);
	while (n > 0)
	{
		*d++ = *s++;
		n--;
	}
	return (dest);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	nbr;
	char	c;

	nbr = n;
	if (nbr < 0)
	{
		(void)!write(fd, "-", 1);
		nbr = -nbr;
	}
	if (nbr / 10)
		ft_putnbr_fd(nbr / 10, fd);
	c = (nbr % 10) + '0';
	(void)!write(fd, &c, 1);
}
