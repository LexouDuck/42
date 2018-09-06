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

static void		shader_diffuse(t_vector *result, t_shader *shader, t_light *light)
{
	light = light;
	vector_invert(&shader->ray.dir);
	shader->ray.t = vector_scalar(&shader->ray.dir, &shader->hit_normal);
	if (shader->ray.t < 0)
		shader->ray.t = 0;
	vector_set(result,
		result->x + shader->light.x * shader->ray.t,
		result->y + shader->light.y * shader->ray.t,
		result->z + shader->light.z * shader->ray.t);
}

static void		shader_specular(t_vector *result, t_shader *shader, t_ray *ray)
{
	vector_invert(&shader->ray.dir);
	shader->ray.t = 2 * vector_scalar(&shader->ray.dir, &shader->hit_normal);
	shader->ray.dir.x -= shader->hit_normal.x * shader->ray.t;
	shader->ray.dir.y -= shader->hit_normal.y * shader->ray.t;
	shader->ray.dir.z -= shader->hit_normal.z * shader->ray.t;
	shader->ray.t = -vector_scalar(&shader->ray.dir, &ray->dir);
	if (shader->ray.t < 0)
		shader->ray.t = 0;
	vector_set(result,
		result->x + shader->light.x * shader->ray.t,
		result->y + shader->light.y * shader->ray.t,
		result->z + shader->light.z * shader->ray.t);
}

static t_u32	shader_getcolor(t_u32 color,
	t_vector *diffuse,
	t_vector *specular)
{
	int	r;
	int	g;
	int	b;

	r = (float)color_get_r(color) * diffuse->x + specular->x;
	g = (float)color_get_g(color) * diffuse->y + specular->y;
	b = (float)color_get_b(color) * diffuse->z + specular->z;
	if (r < 0)
		r = 0;
	else if (r >= 256)
		r = 255;
	if (g < 0)
		g = 0;
	else if (g >= 256)
		g = 255;
	if (b < 0)
		b = 0;
	else if (b >= 256)
		b = 255;
	return (color_new(0, r, g, b));
}

void			shader_init(t_shader *shader)
{
	ft_memcpy(&shader->ray.orig, &shader->hit_pos, sizeof(t_vector));
	shader->ray.orig.x += shader->hit_normal.x * LIGHT_BIAS;
	shader->ray.orig.y += shader->hit_normal.y * LIGHT_BIAS;
	shader->ray.orig.z += shader->hit_normal.z * LIGHT_BIAS;
}

void			shader_setupray(t_shader *shader, t_light *light)
{
	vector_set(&shader->ray.dir,
		shader->hit_pos.x - light->position.x,
		shader->hit_pos.y - light->position.y,
		shader->hit_pos.z - light->position.z);
	vector_set(&shader->light,
		(float)color_get_r(light->color) * light->strength,
		(float)color_get_g(light->color) * light->strength,
		(float)color_get_b(light->color) * light->strength);
	vector_scale(&shader->light, 5 / vector_length(&shader->ray.dir));
	vector_normalize(&shader->ray.dir);
}

t_u32			render_shade(t_rtv1 *rtv1, t_ray *ray, t_shader *shader)
{
	int			render;
	t_list		*lst;
	float		tmp;

	render = rtv1->camera->render;
	tmp = (render & RENDER_DIFFUSE) ? 0.2 : 1;
	vector_set(&shader->diffuse, tmp, tmp, tmp);
	vector_set(&shader->specular, 0, 0, 0);
	shader_init(shader);
	lst = rtv1->lights;
	while (lst)
	{
		shader_setupray(shader, (t_light *)lst->content);
		if (!(render & RENDER_SHADOWS) || !(render_trace(rtv1, &shader->ray)))
		{
			if (render & RENDER_DIFFUSE)
				shader_diffuse(&shader->diffuse, shader, (t_light *)lst->content);
			if (render & RENDER_SPECULAR)
				shader_specular(&shader->specular, shader, ray);
		}
		lst = lst->next;
	}
	return (shader_getcolor(shader->object_color,
		&shader->diffuse, &shader->specular));
}
