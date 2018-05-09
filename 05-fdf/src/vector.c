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

/*
**char		*vector_tostr(t_vector *vector)
**{
**	char	*result;
**
**	if (!(result = (char *)malloc(36)))
**		return (NULL);
**	snprintf(result, 36, "(%f,%f,%f)",
**		vector->x,
**		vector->y,
**		vector->z);
**	return (result);
**}
*/
