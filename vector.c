/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbousque <tbousque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 07:56:25 by tbousque          #+#    #+#             */
/*   Updated: 2022/07/03 02:12:02 by tbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec	vec_new(size_t cap)
{
	t_vec	vec;

	vec.len = 0;
	vec.capacity = 0;
	vec.data = NULL;
	if (!cap)
		return (vec);
	vec.data = malloc(sizeof(char) * cap);
	if (!vec.data)
		return (vec);
	ft_memset(vec.data, 0, vec.capacity);
	vec.capacity = cap;
	return (vec);
}

void	vec_push_back(t_vec *vec, char byte)
{
	char	*tmp_new_alloc;
	size_t	new_cap;

	vec->len++;
	if (vec->len > vec->capacity)
	{
		new_cap = vec->capacity * 2;
		tmp_new_alloc = malloc(sizeof(*vec->data) * new_cap);
		if (!tmp_new_alloc)
		{
			vec_free(vec);
			return ;
		}
		ft_memset(tmp_new_alloc, 0, new_cap);
		ft_memcpy(tmp_new_alloc, vec->data, vec->len - 1);
		free(vec->data);
		vec->data = tmp_new_alloc;
		vec->capacity = new_cap;
	}
	vec->data[vec->len - 1] = byte;
}

void	vec_free(t_vec *vec)
{
	free(vec->data);
	vec->data = NULL;
	vec->capacity = 0;
	vec->len = 0;
}
