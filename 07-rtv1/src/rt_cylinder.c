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
	int			intersect;

	if (!object)
		return (0);
	intersect = 0;
	if ((intersect += intersect_cylinder_base(ray, 1, &tmp)))
		ray->t = (tmp < ray->t) ? tmp : ray->t;
	if ((intersect += intersect_cylinder_base(ray, -1, &tmp)))
		ray->t = (tmp < ray->t) ? tmp : ray->t;
	v.x = ray->dir.x * ray->dir.x + ray->dir.z * ray->dir.z;
	v.y = ray->dir.x * ray->orig.x + ray->dir.z * ray->orig.z;
	v.z = ray->orig.x * ray->orig.x + ray->orig.z * ray->orig.z - 1;
	if ((tmp = v.y * v.y - v.x * v.z) < 0)
		return (intersect ? 1 : 0);
	if ((tmp = (-v.y - sqrt(tmp)) / v.x) <= 0)
		return (intersect ? 1 : 0);
	if (tmp >= ray->t)
		return (intersect ? 1 : 0);
	ray->t = tmp;
	tmp = ray->orig.y + ray->dir.y * ray->t;
	return ((-1 <= tmp && tmp <= 1) ? 1 : intersect);
}

void		getnormal_cylinder(t_vector *result, t_object *object, t_vector *hit_pos)
{
	t_vector	vector;

	vector_set(&vector,
		(hit_pos->x - object->position.x) / object->scale.x,
		(hit_pos->y - object->position.y) / object->scale.y,
		(hit_pos->z - object->position.z) / object->scale.z);
	vector_transform(&vector, &object->matrix);
	if (vector.y >= 1)
		vector_set(result, 0, 1, 0);
	else if (vector.y <= -1)
		vector_set(result, 0, -1, 0);
	else
 		vector_set(result, vector.x, 0, vector.z);
	vector_transform(result, &object->matrix_toworld);
 	vector_normalize(result);
}
