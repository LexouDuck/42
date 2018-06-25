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
	t_u32	color;

	color = 0xFFFFFF;
	mlx_string_put(mlx, win, 10, 20, color, "CAMERA->");
	mlx_string_put(mlx, win, 60, 20, color, ft_itoa(camera->render));
	mlx_string_put(mlx, win, 10, 40, color, "Anchor:");
	mlx_string_put(mlx, win, 60, 40, color, vector_tostr(&camera->anchor, 3));
	mlx_string_put(mlx, win, 10, 60, color, "Vector:");
	mlx_string_put(mlx, win, 60, 60, color, vector_tostr(&camera->pos, 3));
	mlx_string_put(mlx, win, 10, 80, color, "Lat:");
	mlx_string_put(mlx, win, 50, 80, color, ft_ftoa(camera->lat, 8));
	mlx_string_put(mlx, win, 10, 100, color, "Lon:");
	mlx_string_put(mlx, win, 50, 100, color, ft_ftoa(camera->lon, 8));
	mlx_string_put(mlx, win, 10, 120, color, "Zoom:");
	mlx_string_put(mlx, win, 50, 120, color, ft_ftoa(camera->zoom, 8));
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
	return (result);
}

/*
static t_u32	render_shade(t_rtv1 *rtv1, t_vector *dir, t_vector *hit_normal)
{
	t_light		*light;
	t_object 	*object;
	t_ray		ray;
	float		tmp;
	float		result;

	ray.orig = (vector_scalar(dir, hit_normal) < 0) ?
		hit_pos + hit_normal * 0.00001 :
		hit_pos - hit_normal * 0.00001;

	lst = rtv1->lights;
	while (lst)
	{
		t_vector ray.dir = light->position - hitPoint;
		ray.dir = vector_normalize(ray.dir);
		float LdotN = std::max(0.f, vector_scalar(ray.dir, hit_normal));
		object = NULL;
		if (!(object = render_trace(rtv1, ray)) &&
			(ray.t * ray.t < vector_scalar(ray.dir, ray.dir)))
		// is the point in shadow, and is the nearest occluding object closer to the object than the light itself?
			lightAmt += light->strength * LdotN;
		t_vector reflectionDirection = -ray.dir - 2 * vector_scalar(-ray.dir, hit_normal) * hit_normal;
		specularColor += powf(std::max(0.f, -vector_scalar(reflectionDirection, dir)), hitObject->specularExponent) * light->strength;
		lst = lst->next;
	}
	hitColor = lightAmt * hitObject->evalDiffuseColor(st) * hitObject->Kd + specularColor * hitObject->Ks;
	break;
}
*/

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

		vector_set(&hit_pos,
			ray->orig.x + ray->dir.x * ray->t,
			ray->orig.y + ray->dir.y * ray->t,
			ray->orig.z + ray->dir.z * ray->t);
		/*
		ft_putstr("HITPOS: ");
		ft_putstr(ft_ftoa(hit_pos.x, 10));	ft_putstr(", ");
		ft_putstr(ft_ftoa(hit_pos.y, 10));	ft_putstr(", ");
		ft_putstr(ft_ftoa(hit_pos.z, 10));	ft_putstr("\n");
		*/
		vector_set(&hit_normal,
			hit_pos.x - object->position.x,
			hit_pos.y - object->position.y,
			hit_pos.z - object->position.z);
		vector_normalize(&hit_normal);
		/*
		ft_putstr("NORMAL: ");
		ft_putstr(ft_ftoa(hit_normal.x, 10));	ft_putstr(", ");
		ft_putstr(ft_ftoa(hit_normal.y, 10));	ft_putstr(", ");
		ft_putstr(ft_ftoa(hit_normal.z, 10));	ft_putstr("\n");
		*/
		result = object->color;
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
