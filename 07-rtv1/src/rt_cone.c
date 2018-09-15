/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cone.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

static int	intersect_cone_base(t_ray *ray, float base, float *t)
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

int		intersect_cone(t_object *object, t_ray *ray)
{
	t_vector	v;
	t_vector	t;
	float		tmp;

	t.x = ray->orig.x - object->position.x;
	t.y = ray->orig.z - object->position.z;
	t.z = 1 - ray->orig.y + object->position.y;
	v.x = (ray->dir.x * ray->dir.x) + (ray->dir.z * ray->dir.z) -
		(ray->dir.y * ray->dir.y);
	v.y = (2 * t.x * ray->dir.x) + (2 * t.y * ray->dir.z) +
		(2 * t.z * ray->dir.y);
	v.z = (t.x * t.x) + (t.y * t.y) - (t.z * t.z);
	tmp = v.y * v.y - 4 * (v.x * v.z);
	if (tmp <= 0)
		return (0);
	t.x = (-v.y - sqrt(tmp)) / (2 * v.x);
	t.y = (-v.y + sqrt(tmp)) / (2 * v.x);
	ray->t = (t.x <= t.y) ? t.x : t.y;
	tmp = ray->orig.y + ray->t * ray->dir.y;
	if (object->position.y < tmp && tmp < object->position.y + 1)
		return (1);
	if (intersect_cone_base(ray, 0, &ray->t))
		return (1);
	return (0);
}

void	getnormal_cone(t_vector *result, t_object *object, t_vector *hit_pos)
{
	t_vector	vector;
    float		tmp;

	vector_set(&vector,
		hit_pos->x - object->position.x,
		hit_pos->y - object->position.y,
		hit_pos->z - object->position.z);
	vector_normalize(&vector);
	vector_transform(&vector, &object->matrix);
    if (vector.y <= 0.0)
    {
    	vector_set(&vector, 0, -1, 0);
		vector_transform(&vector, &object->matrix_toworld);
		vector_normalize(&vector);
		vector_set(result, vector.x, vector.y, vector.z);
    }
    else
    {
	    tmp = sqrt(
	    	(hit_pos->x - object->position.x) * (hit_pos->x - object->position.x) +
	    	(hit_pos->z - object->position.z) * (hit_pos->z - object->position.z));
	    vector_set(result,
	    	hit_pos->x - object->position.x, tmp, hit_pos->z - object->position.z);
	    vector_normalize(result);
    }
}
