/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbousque <tbousque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 07:56:15 by tbousque          #+#    #+#             */
/*   Updated: 2022/07/01 08:13:06 by tbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H
# include <stddef.h>
# include <stdlib.h>
typedef struct s_vec
{
	size_t	capacity;
	size_t	len;
	char	*data;
}	t_vec;

t_vec	vec_new(size_t cap);
void	vec_push_back(t_vec *vec, char byte);
void	vec_free(t_vec *vec);
#endif