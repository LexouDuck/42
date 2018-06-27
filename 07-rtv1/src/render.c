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

void				get_camera_matrix(t_camera *camera)
{
	t_vector	*vector;
	t_vector	*axis_forward;
	t_vector	*axis_right;
	t_vector	*axis_up;

	axis_forward = vector_new(camera->pos.x, camera->pos.y, camera->pos.z);
	vector_normalize(axis_forward);
	if (axis_forward->x == 0 && axis_forward->z == 0 &&
		(axis_forward->y == 1 || axis_forward->y == -1))
		axis_forward->z = 0.00001;
	axis_right = vector_multiply(&camera->tilt, axis_forward);
	vector_normalize(axis_right);
	axis_up = vector_multiply(axis_forward, axis_right);
	matrix_set(&camera->matrix, axis_right, axis_up, axis_forward);
	vector = vector_new(
		camera->anchor.x + camera->pos.x,
		camera->anchor.y + camera->pos.y,
		camera->anchor.z + camera->pos.z);
	/*matrix_transpose(&camera->matrix);
	vector_set(vector,
		-vector_scalar(vector, axis_right),
		-vector_scalar(vector, axis_up),
		-vector_scalar(vector, axis_forward));
	*/
	camera->matrix.t = vector;
}

static void		render_debug(void *mlx, void *win, t_camera *camera)
{
	char	*str;
	t_u32	color;

	color = 0xFFFFFF;
	str = vector_tostr(&camera->anchor, 3);
	mlx_string_put(mlx, win, 10, 40, color, "Anchor:");
	mlx_string_put(mlx, win, 60, 40, color, str);
	free(str);
	str = vector_tostr(&camera->pos, 3);
	mlx_string_put(mlx, win, 10, 60, color, "Vector:");
	mlx_string_put(mlx, win, 60, 60, color, str);
	free(str);
	str = ft_ftoa(camera->lat, 8);
	mlx_string_put(mlx, win, 10, 80, color, "Lat:");
	mlx_string_put(mlx, win, 50, 80, color, str);
	free(str);
	str = ft_ftoa(camera->lon, 8);
	mlx_string_put(mlx, win, 10, 100, color, "Lon:");
	mlx_string_put(mlx, win, 50, 100, color, str);
	free(str);
	str = ft_ftoa(camera->zoom, 8);
	mlx_string_put(mlx, win, 10, 120, color, "Zoom:");
	mlx_string_put(mlx, win, 50, 120, color, str);
	free(str);
}

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
	result = 0.1;
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
	t_u32 shine = specular * 256;
	t_u32 c_r = color_get_r(color) * result + shine; if (c_r >= 256) c_r = 255;
	t_u32 c_g = color_get_g(color) * result + shine; if (c_g >= 256) c_g = 255;
	t_u32 c_b = color_get_b(color) * result + shine; if (c_b >= 256) c_b = 255;
	return (color_new(0, c_r, c_g, c_b));
}

static t_u32	render_cast_ray(t_rtv1 *rtv1, t_ray *ray)
{
	t_u32		result;
	t_object	*object;

	result = rtv1->bg_color;
	object = NULL;
	if ((object = render_trace(rtv1, ray)))
	{
		t_vector hit_pos;
		t_vector hit_normal;

		vector_invert(&ray->dir);
		vector_set(&hit_pos,
			ray->orig.x + ray->dir.x * ray->t,
			ray->orig.y + ray->dir.y * ray->t,
			ray->orig.z + ray->dir.z * ray->t);
		/*
		if (hit_pos.x || hit_pos.y || hit_pos.z) {
		ft_putstr("HITPOS: ");
		ft_putstr(ft_ftoa(hit_pos.x, 10));	ft_putstr(", ");
		ft_putstr(ft_ftoa(hit_pos.y, 10));	ft_putstr(", ");
		ft_putstr(ft_ftoa(hit_pos.z, 10));	ft_putstr("\n");
		}
		*/
		vector_set(&hit_normal,
			hit_pos.x - object->position.x,
			hit_pos.y - object->position.y,
			hit_pos.z - object->position.z);
		vector_normalize(&hit_normal);
		/*
		if (hit_normal.x || hit_normal.y || hit_normal.z) {
		ft_putstr("NORMAL: ");
		ft_putstr(ft_ftoa(hit_normal.x, 10));	ft_putstr(", ");
		ft_putstr(ft_ftoa(hit_normal.y, 10));	ft_putstr(", ");
		ft_putstr(ft_ftoa(hit_normal.z, 10));	ft_putstr("\n");
		}
		*/
		result = render_shade(rtv1, object->color, ray, &hit_pos, &hit_normal);
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
	vector_set(&ray.orig, 0, 0, 0);
	vector_transform(&ray.orig, matrix);
	tmp = matrix->t;
	pixel.color = 0;
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
			buffer[pixel.color++] = render_cast_ray(rtv1, &ray);
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
