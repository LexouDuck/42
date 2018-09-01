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

static void	shader_diffuse(float *result,
	t_shader *shader, t_light *light, t_rtv1 *rtv1)
{
	t_object	*object;
	float		light_distance;

	shader->ray.dir.x = light->position.x - shader->hit_pos.x;
	shader->ray.dir.y = light->position.y - shader->hit_pos.y;
	shader->ray.dir.z = light->position.z - shader->hit_pos.z;
	light_distance = vector_scalar(&shader->ray.dir, &shader->ray.dir);
	vector_normalize(&shader->ray.dir);
	object = NULL;
	if (!(object = render_trace(rtv1, &shader->ray)) ||
		(shader->ray.t * shader->ray.t < light_distance))
	{
/*
ft_putstr("t: ");
ft_putstr(ft_ftoa(shader->ray.t, 6));
ft_putstr(", distance: ");
ft_putendl(ft_ftoa(light_distance, 6));
*/
		shader->ray.t = vector_scalar(&shader->ray.dir, &shader->hit_normal);
		if (shader->ray.t < 0)
			shader->ray.t = 0;
		*result += light->strength * shader->ray.t;
	}
}

static void	shader_specular(float *result,
	t_shader *shader, t_light *light, t_ray *ray)
{
	t_vector	reflection;

	ft_memcpy(&reflection, &shader->ray.dir, sizeof(t_vector));
	vector_invert(&reflection);
	shader->ray.t = 2 * vector_scalar(&reflection, &shader->hit_normal);
	reflection.x -= shader->hit_normal.x * shader->ray.t;
	reflection.y -= shader->hit_normal.y * shader->ray.t;
	reflection.z -= shader->hit_normal.z * shader->ray.t;
	shader->ray.t = -vector_scalar(&reflection, &ray->dir);
	if (shader->ray.t < 0)
		shader->ray.t = 0;
	*result += light->strength * shader->ray.t;
}

t_u32		render_shade(t_rtv1 *rtv1, t_ray *ray, t_shader *shader)
{
	t_light		*light;
	float		diffuse;
	float		specular;
	t_list		*lst;

	ft_memcpy(&shader->ray.orig, &shader->hit_normal, sizeof(t_vector));
	vector_scale(&shader->ray.orig, 0.00001);
	if (vector_scalar(&ray->dir, &shader->hit_normal) < 0)
		vector_invert(&shader->ray.orig);
	shader->ray.orig.x += shader->hit_pos.x;
	shader->ray.orig.y += shader->hit_pos.y;
	shader->ray.orig.z += shader->hit_pos.z;
	diffuse = 0.2;
	specular = 0;
	lst = rtv1->lights;
	while (lst)
	{
		light = (t_light *)lst->content;
		shader_diffuse(&diffuse, shader, light, rtv1);
		shader_specular(&specular, shader, light, ray);
		lst = lst->next;
	}
	specular *= 50;
	int c_r = (float)color_get_r(shader->object_color) * diffuse + specular; if (c_r < 0) c_r = 0; else if (c_r >= 256) c_r = 255;
	int c_g = (float)color_get_g(shader->object_color) * diffuse + specular; if (c_g < 0) c_g = 0; else if (c_g >= 256) c_g = 255;
	int c_b = (float)color_get_b(shader->object_color) * diffuse + specular; if (c_b < 0) c_b = 0; else if (c_b >= 256) c_b = 255;
	return (color_new(0, c_r, c_g, c_b));
}
