/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cube.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

static void	intersect_cube_axis(
	float *tmin, float *tmax,
	float orig, float dir)
{
	float	invdir;
	float	coord;

	invdir = (1 / dir);
	coord = (invdir < 0) ? -1 : 1;
	*tmin = (coord - orig) * invdir;
	*tmax = (-coord - orig) * invdir;
	if (*tmin > *tmax)
	{
		coord = *tmin;
		*tmin = *tmax;
		*tmax = coord;
	}
}

int			intersect_cube(t_object *object, t_ray *ray)
{
	t_vector	min;
	t_vector	max;

	if (!object)
		return (0);
	intersect_cube_axis(&min.x, &max.x, ray->orig.x, ray->dir.x);
	intersect_cube_axis(&min.y, &max.y, ray->orig.y, ray->dir.y);
	if ((min.x > max.y) || (min.y > max.x))
		return (0);
	if (min.y > min.x)
		min.x = min.y;
	if (max.y < max.x)
		max.x = max.y;
	intersect_cube_axis(&min.z, &max.z, ray->orig.z, ray->dir.z);
	if ((min.x > max.z) || (min.z > max.x))
		return (0);
	if (min.z > min.x)
		min.x = min.z;
	if (max.z < max.x)
		max.x = max.z;
	ray->t = (min.x < max.x) ? min.x : max.x;
	return (1);
}

void	getnormal_cube(t_vector *result, t_object *object, t_vector *hit_pos)
{
	t_matrix	matrix;
	t_vector	u;
	t_vector	v;
	t_vector	w;
	t_vector	vector;

	vector_set(&vector,
		hit_pos->x - object->position.x,
		hit_pos->y - object->position.y,
		hit_pos->z - object->position.z);
	vector_transform(&vector, &object->matrix);
	if (vector.x == vector.y && vector.y == vector.z)
	{
		vector_set(result, vector.x, vector.y, vector.z);
		return ;
	}
	else if (vector.x >= vector.y && vector.x >= vector.z) {vector.y = 0;vector.z = 0;}
	else if (vector.y >= vector.x && vector.y >= vector.z) {vector.x = 0;vector.z = 0;}
	else if (vector.z >= vector.x && vector.z >= vector.y) {vector.x = 0;vector.y = 0;}
	ft_memcpy(&u, object->matrix.u, sizeof(t_vector));
	ft_memcpy(&v, object->matrix.v, sizeof(t_vector));
	ft_memcpy(&w, object->matrix.w, sizeof(t_vector));
	matrix.t = NULL;
	matrix_set(&matrix, &u, &v, &w);
	matrix_inverse(&matrix);
	vector_transform(&vector, &matrix);
	vector_normalize(&vector);
	vector_set(result, vector.x, vector.y, vector.z);
}
