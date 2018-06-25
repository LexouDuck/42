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

#include "../rtv1.h"

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


char		*vector_tostr(t_vector *vector, int precision)
{
	char	*x; int x_len;
	char	*y; int y_len;
	char	*z; int z_len;
	char	*result;
	int		i;

	x = ft_ftoa(vector->x, precision);
	y = ft_ftoa(vector->y, precision);
	z = ft_ftoa(vector->z, precision);
	x_len = ft_strlen(x);
	y_len = ft_strlen(y);
	z_len = ft_strlen(z);
	if (!(result = (char *)malloc(x_len + y_len + z_len + 7)))
		return (NULL);
	i = 0;
	result[i++] = '(';
	ft_memcpy(result + i, x, x_len); i += x_len; result[i++] = ','; result[i++] = ' ';
	ft_memcpy(result + i, y, y_len); i += y_len; result[i++] = ','; result[i++] = ' ';
	ft_memcpy(result + i, z, z_len); i += z_len; result[i++] = ')'; result[i++] = '\0';
	return (result);
}

