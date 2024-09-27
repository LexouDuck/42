/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

t_vector	*vector_new(float x, float y, float z)
{
	t_vector *result;

	if (!(result = (t_vector *)malloc(sizeof(t_vector))))
		return (NULL);
	result->x = x;
	result->y = y;
	result->z = z;
	return (result);
}

inline void	vector_set(t_vector *vector, float x, float y, float z)
{
	vector->x = x;
	vector->y = y;
	vector->z = z;
}

float		vector_length(t_vector const *vector)
{
	float	tmp;
	float	sum;

	sum = 0;
	tmp = vector->x;
	tmp *= tmp;
	sum += tmp;
	tmp = vector->y;
	tmp *= tmp;
	sum += tmp;
	tmp = vector->z;
	tmp *= tmp;
	sum += tmp;
	return (sum);
}

inline void	vector_scale(t_vector *vector, float scale)
{
	vector->x *= scale;
	vector->y *= scale;
	vector->z *= scale;
}

char		*vector_tostr(t_vector *vector, int i)
{
	t_tuple	x;
	t_tuple	y;
	t_tuple	z;
	char	*result;

	x.items = ft_f32_to_str(vector->x, i);
	y.items = ft_f32_to_str(vector->y, i);
	z.items = ft_f32_to_str(vector->z, i);
	x.length = ft_strlen(x.items);
	y.length = ft_strlen(y.items);
	z.length = ft_strlen(z.items);
	if (!(result = (char *)malloc(x.length + y.length + z.length + 7)))
		return (NULL);
	i = 0;
	result[i++] = '(';
	if (ft_memcpy(result + i, x.items, x.length) && (i += x.length + 2))
		free(x.items);
	ft_memcpy(result + i - 2, ", ", 2);
	if (ft_memcpy(result + i, y.items, y.length) && (i += y.length + 2))
		free(y.items);
	ft_memcpy(result + i - 2, ", ", 2);
	if (ft_memcpy(result + i, z.items, z.length) && (i += z.length + 2))
		free(z.items);
	ft_memcpy(result + i - 2, ")\0", 2);
	return (result);
}
