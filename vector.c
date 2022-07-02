/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbousque <tbousque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 07:56:25 by tbousque          #+#    #+#             */
/*   Updated: 2022/07/01 08:23:08 by tbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec	vec_new(size_t cap)
{
	t_vec vec;

	vec.len = 0;
	vec.capacity = 0;
	vec.data = NULL;
	if (!cap)
		return (vec);
	vec.data = malloc(sizeof(char) * cap);
	if (!vec.data)
		return (vec);
	vec.capacity = cap;
	return (vec);
}

# include <string.h>

void	vec_push_back(t_vec *vec, char byte)
{
	char	*tmp_new_alloc;

	vec->len += 1;
	if (vec->len > vec->capacity)
	{
		tmp_new_alloc = malloc(sizeof(*vec->data) * vec->capacity);
		if (!tmp_new_alloc)
		{
			vec_free(vec);
			return ;
		}
		memcpy(tmp_new_alloc, vec->data, vec->capacity);
		vec->capacity *= 2;
		free(vec->data);
		vec->data = tmp_new_alloc;
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