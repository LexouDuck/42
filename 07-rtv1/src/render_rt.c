/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_rt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

t_object		*render_trace(t_rtv1 *rtv1, t_ray *ray)
{
	t_object	*result;
	t_camera	*camera;
	t_object	*object;
	t_list		*lst;
	float		t;

	result = NULL;
	camera = rtv1->camera;
	t = camera->range_max;
	lst = rtv1->objects;
	while (lst)
	{
		ray->t = camera->range_max;
		object = (t_object *)lst->content;
		if (object->intersect(object, ray) && (ray->t < t))
		{
			result = object;
			t = ray->t;
		}
		lst = lst->next;
	}
	ray->t = t;
	return (result);
}

static t_u32	render_shade(t_rtv1 *rtv1,
	t_u32 color, t_ray *ray,
	t_vector *hit_pos, t_vector *hit_normal)
{
	t_light		*light;
	t_object	*object;
	t_ray		lightray;
	float		light_distance;
	t_vector	reflection;
	float		specular;
	float		result;
	t_list		*lst;

	ft_memcpy(&lightray.orig, hit_normal, sizeof(t_vector));
	//vector_scale(&lightray.orig, 0.00001);
	if (vector_scalar(&ray->dir, hit_normal) < 0)
		vector_invert(&lightray.orig);
	lightray.orig.x += hit_pos->x;
	lightray.orig.y += hit_pos->y;
	lightray.orig.z += hit_pos->z;
	specular = 0;
	result = 0.2;
	lst = rtv1->lights;
	while (lst)
	{
		light = (t_light *)lst->content;
		lightray.dir.x = light->position.x - hit_pos->x;
		lightray.dir.y = light->position.y - hit_pos->y;
		lightray.dir.z = light->position.z - hit_pos->z;
		light_distance = vector_scalar(&lightray.dir, &lightray.dir);
		vector_normalize(&lightray.dir);
		object = NULL;
		if (!(object = render_trace(rtv1, &lightray)) ||
			(lightray.t * lightray.t < light_distance))
		{
/*
ft_putstr("t: ");
ft_putstr(ft_ftoa(lightray.t, 6));
ft_putstr(", distance: ");
ft_putendl(ft_ftoa(light_distance, 6));
*/
			lightray.t = vector_scalar(&lightray.dir, hit_normal);
			if (lightray.t < 0)
				lightray.t = 0;
			result += light->strength * lightray.t;
		}
		ft_memcpy(&reflection, &lightray.dir, sizeof(t_vector));
		vector_invert(&reflection);
		lightray.t = 2 * vector_scalar(&reflection, hit_normal);
		reflection.x -= hit_normal->x * lightray.t;
		reflection.y -= hit_normal->y * lightray.t;
		reflection.z -= hit_normal->z * lightray.t;
		lightray.t = -vector_scalar(&reflection, &ray->dir);
		if (lightray.t < 0)
			lightray.t = 0;
		specular += light->strength * lightray.t;
		lst = lst->next;
	}
	t_u32 shine = specular * 80;
	t_u32 c_r = color_get_r(color) * result + shine; if (c_r >= 256) c_r = 255;
	t_u32 c_g = color_get_g(color) * result + shine; if (c_g >= 256) c_g = 255;
	t_u32 c_b = color_get_b(color) * result + shine; if (c_b >= 256) c_b = 255;
	return (color_new(0, c_r, c_g, c_b));
}

t_u32			render_cast_ray(t_rtv1 *rtv1, t_ray *ray)
{
	t_u32		result;
	t_object	*object;
	t_vector	hit_pos;
	t_vector	hit_normal;

	result = rtv1->bg_color;
	object = NULL;
	if ((object = render_trace(rtv1, ray)))
	{
		vector_invert(&ray->dir);
		vector_set(&hit_pos,
			ray->orig.x + ray->dir.x * ray->t,
			ray->orig.y + ray->dir.y * ray->t,
			ray->orig.z + ray->dir.z * ray->t);
		object->getnormal(&hit_normal, object, &hit_pos);
		result = render_shade(rtv1, object->color, ray, &hit_pos, &hit_normal);
	}
	return (result);
}
