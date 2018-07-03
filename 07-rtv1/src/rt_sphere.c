/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

static int	solve_quadratic(t_vector *e, float *t0, float *t1)
{
	float	q;
	float	discrim;

	discrim = e->y * e->y - 4 * e->x * e->z;
	if (discrim < 0)
		return (0);
	else if (discrim == 0)
	{
		*t0 = -0.5 * e->y / e->x;
		*t1 = *t0;
	}
	else
	{
		q = (e->y > 0) ?
			-0.5 * (e->y + sqrt(discrim)) :
			-0.5 * (e->y - sqrt(discrim));
		*t0 = q / e->x;
		*t1 = e->z / q;
	}
	return (1);
}

int			intersect_sphere(t_object *object, t_ray *ray)
{
	t_vector	quadratic;
	float		t0;
	float		t1;

	quadratic.x = vector_scalar(&ray->dir, &ray->dir);
	quadratic.y = vector_scalar(&ray->dir, &ray->orig) * 2;
	quadratic.z = vector_scalar(&ray->orig, &ray->orig) - 1;
	if (!object || !solve_quadratic(&quadratic, &t0, &t1))
		return (0);
	if (t0 > t1)
		ft_swap(&t0, &t1, sizeof(float)); 
	if (t0 < 0)
	{
		t0 = t1;
		if (t0 < 0)
			return (0);
	}
	ray->t = t0;
	return (1);
}

void		getnormal_sphere(t_vector *result, t_object *object, t_vector *hit_pos)
{
	vector_set(result,
		hit_pos->x - object->position.x,
		hit_pos->y - object->position.y,
		hit_pos->z - object->position.z);
	vector_normalize(result);
}
