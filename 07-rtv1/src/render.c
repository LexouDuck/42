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
	mlx_string_put(mlx, win, 10, 20, color, "Anchor:");
	mlx_string_put(mlx, win, 60, 20, color, str);
	free(str);
	str = vector_tostr(&camera->pos, 3);
	mlx_string_put(mlx, win, 10, 40, color, "Vector:");
	mlx_string_put(mlx, win, 60, 40, color, str);
	free(str);
	str = ft_ftoa(camera->lat, 8);
	mlx_string_put(mlx, win, 10, 60, color, "Lat:");
	mlx_string_put(mlx, win, 50, 60, color, str);
	free(str);
	str = ft_ftoa(camera->lon, 8);
	mlx_string_put(mlx, win, 10, 80, color, "Lon:");
	mlx_string_put(mlx, win, 50, 80, color, str);
	free(str);
	str = ft_ftoa(camera->zoom, 8);
	mlx_string_put(mlx, win, 10, 99, color, "Zoom:");
	mlx_string_put(mlx, win, 50, 99, color, str);
	free(str);
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
