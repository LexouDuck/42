/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
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
	t_object	*object;
	t_ray		tmp;
	t_list		*lst;
	float		nearest;

	result = NULL;
	nearest = rtv1->camera->range_max;
	lst = rtv1->objects;
	while (lst)
	{
		object = (t_object *)lst->content;
		ft_memcpy(&tmp, ray, sizeof(t_ray));
		tmp.t = nearest;
		set_ray_to_object_space(&tmp, object);
		if (object->intersect(object, &tmp) && (tmp.t < nearest))
		{
			result = object;
			nearest = tmp.t;
		}
		lst = lst->next;
	}
	ray->t = nearest;
	return (result);
}

static t_u32	render_cast_ray(t_rtv1 *rtv1, t_ray *ray)
{
	t_u32		result;
	t_shader	shader;
	t_object	*object;

	result = rtv1->bg_color;
	object = NULL;
	if ((object = render_trace(rtv1, ray)))
	{
		vector_invert(&ray->dir);
		vector_set(&shader.hit_pos,
			ray->orig.x + ray->dir.x * ray->t,
			ray->orig.y + ray->dir.y * ray->t,
			ray->orig.z + ray->dir.z * ray->t);
		object->getnormal(&shader.hit_normal, object, &shader.hit_pos);
		shader.object_color = object->color;
		result = render_shade(rtv1, ray, &shader);
	}
	return (result);
}

static void		render_pixels(t_rtv1 *rtv1, t_u32 *buffer,
	float scale, float ratio)
{
	t_vector	*tmp;
	t_matrix	*matrix;
	t_ray		ray;
	t_point		pixel;

	matrix = &rtv1->camera->matrix;
	tmp = matrix->t;
	vector_set(&ray.orig, 0, 0, 0);
	vector_transform(&ray.orig, matrix);
	pixel.color = WIDTH * HEIGHT;
	pixel.y = -1;
	while (++pixel.y < HEIGHT)
	{
		pixel.x = -1;
		while (++pixel.x < WIDTH)
		{
			vector_set(&ray.dir,
				(2 * ((pixel.x + 0.5) / (float)WIDTH) - 1) * scale * ratio,
				(1 - 2 * ((pixel.y + 0.5) / (float)HEIGHT)) * scale, 1);
			matrix->t = NULL;
			vector_transform(&ray.dir, matrix);
			vector_normalize(&ray.dir);
			matrix->t = tmp;
			buffer[--pixel.color] = render_cast_ray(rtv1, &ray);
		}
	}
}

void			render(t_mlx *mlx, t_camera *camera)
{
	t_u32		*buffer = (t_u32 *)mlx->image->buffer;

	ft_bzero(buffer, HEIGHT * mlx->image->line);
	camera_update(camera);
	get_camera_matrix(camera);
	render_pixels(mlx->rtv1, buffer,
		tan(camera->fov * 0.5 * M_PI / 180),
		((float)WIDTH / (float)HEIGHT));
	mlx_put_image_to_window(
		mlx->mlx_ptr,
		mlx->win_ptr,
		mlx->img_ptr, 0, 0);
	render_debug(mlx->mlx_ptr, mlx->win_ptr, camera);
	free(camera->matrix.u);
	free(camera->matrix.v);
	free(camera->matrix.w);
	free(camera->matrix.t);
}
