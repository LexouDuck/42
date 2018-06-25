/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

int	intersect_plane(t_object *object, t_ray *ray)
{
	if (object && ray)
		return (0);
	return (1);
}

int	intersect_triangle(t_object *object, t_ray *ray)
{
	if (object && ray)
		return (0);
	return (1);
}

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

int	intersect_sphere(t_object *object, t_ray *ray)
{
	t_vector	vector;
	t_vector	quadratic;
	float		t0;
	float		t1;

	vector_set(&vector,
		object->position.x - ray->orig.x,
		object->position.y - ray->orig.y,
		object->position.z - ray->orig.z);
	quadratic.x = vector_scalar(&ray->dir, &ray->dir);
	quadratic.y = vector_scalar(&ray->dir, &vector) * 2;
	quadratic.z = vector_scalar(&vector, &vector);
	quadratic.z -= (object->scale.x * object->scale.x);
	if (!solve_quadratic(&quadratic, &t0, &t1))
		return (0);
	if (t0 < 0)
	{
		t0 = t1;
		if (t0 < 0)
			return (0);
	}
	ray->t = t0;
	return (1);
}
/*
int	intersect_sphere(t_object *object, t_ray *ray)
{
	t_vector	vector;
	t_vector	t;
	t_vector	d;

	vector_set(&vector,
		object->position.x - ray->orig.x,
		object->position.y - ray->orig.y,
		object->position.z - ray->orig.z);
	t.z = vector_scalar(&vector, &ray->dir);
	if (t.z < 0)
		return (0);
	d.x = vector_scalar(&vector, &vector) - t.z * t.z;
	d.y = (object->scale.x * object->scale.x);
	if (d.x > d.y)
		return (0);
	d.z = sqrt(d.y - d.x);
	t.x = t.z - d.z;
	t.y = t.z + d.z;
	if (t.x > t.y)
		ft_swap(&t.x, &t.y, sizeof(float));
	if (t.x < 0)
	{
		t.x = t.y; // if t.x is negative, let's use t.y instead
		if (t.x < 0)
			return (0); // both t.y and t.y are negative
	}
	ray->t = t.x;
	return (1);
}
*/
int	intersect_cylinder(t_object *object, t_ray *ray)
{
	if (object && ray)
		return (0);
	return (1);
}

int	intersect_cone(t_object *object, t_ray *ray)
{
	if (object && ray)
		return (0);
	return (1);
}
