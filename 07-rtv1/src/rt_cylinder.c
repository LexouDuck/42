/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

static int	intersect_cylinder_base(t_ray *ray, float base, float *t)
{
	t_vector	v;
	float		tmp;
	float		distance;

	tmp = -(base * base);
	if (base * ray->dir.y == 0)
		return (0);
	distance = -(base * ray->orig.y + tmp);
	distance /= (base * ray->dir.y);
	if (distance < 0)
		return (0);
	v.x = ray->orig.x + distance * ray->dir.x;
	v.y = ray->orig.y + distance * ray->dir.y;
	v.z = ray->orig.z + distance * ray->dir.z;
	if (v.x * v.x + v.z * v.z - 1 > 0)
		return (0);
	*t = distance;
	return (1);
}

int			intersect_cylinder(t_object *object, t_ray *ray)
{
	t_vector	v;
	float		tmp;
	int			result;

	v.x = ray->dir.x * ray->dir.x + ray->dir.z * ray->dir.z;
	v.y = ray->dir.x * ray->orig.x + ray->dir.z * ray->orig.z;
	v.z = ray->orig.x * ray->orig.x + ray->orig.z * ray->orig.z - 1;
	if ((tmp = v.y * v.y - v.x * v.z) < 0 || !object)
		return (0);
	if ((ray->t = (-v.y - sqrt(tmp)) / v.x) <= 0)
		return (0);
	tmp = ray->orig.y + ray->dir.y * ray->t;
	if (tmp >= 1 || tmp <= -1)
	{
		result = 0;
		if ((result += 2 * intersect_cylinder_base(ray, 1, &tmp)))
			ray->t = (tmp < ray->t) ? tmp : ray->t;
		if ((result += intersect_cylinder_base(ray, -1, &tmp)) & 1)
			ray->t = (tmp < ray->t) ? tmp : ray->t;
		return (result ? 1 : 0);
	}
	return (1);
}

void		getnormal_cylinder(t_vector *result, t_object *object, t_vector *hit_pos)
{
	t_vector	vector;

	vector_set(&vector,
		hit_pos->x - object->position.x,
		hit_pos->y - object->position.y,
		hit_pos->z - object->position.z);
	vector_normalize(&vector);
	vector_transform(&vector, &object->matrix);
	if (vector.y >= 1)
		vector_set(result, 0, 1, 0);
	else if (vector.y <= -1)
		vector_set(result, 0, -1, 0);
	else
 		vector_set(result, vector.x, 0, vector.z);
	vector_transform(result, &object->matrix_toworld);
 	vector_normalize(result);
 	return ;
}
