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

/*
**static void		render_debug(t_mlx *mlx, t_camera *camera, t_matrix *matrix)
**{
**	int		length;
**	char	*str;
**
**	length = 48;
**	if (!(str = (char *)malloc(length)))
**		return ;
**	snprintf(str, length, "%f,%f, %f", camera->lat, camera->lon, camera->zoom);
**	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 20, 0xFFFFFF, "CAMERA->");
**	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 60, 20, 0xFFFFFF, ft_itoa(camera->render));
**	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 40, 0xFFFFFF, "Anchor:");
**	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 60, 40, 0xFFFFFF, vector_tostr(&camera->anchor));
**	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 60, 0xFFFFFF, "Vector:");
**	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 60, 60, 0xFFFFFF, vector_tostr(&camera->pos));
**	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 80, 0xFFFFFF, "Lat,Lon,Zoom:");
**	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 90, 80, 0xFFFFFF, str);
**
**	snprintf(str, length, "u:(%f,%f,%f)", matrix->u->x, matrix->u->y, matrix->u->z);
**	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 300, 20, 0xFFFFFF, str);
**	snprintf(str, length, "v:(%f,%f,%f)", matrix->v->x, matrix->v->y, matrix->v->z);
**	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 300, 40, 0xFFFFFF, str);
**	snprintf(str, length, "w:(%f,%f,%f)", matrix->w->x, matrix->w->y, matrix->w->z);
**	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 300, 60, 0xFFFFFF, str);
**	if (matrix->t)	snprintf(str, length, "t:(%f,%f,%f)", matrix->t->x, matrix->t->y, matrix->t->z);
**	else			snprintf(str, length, "t:(NULL)");
**	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 300, 80, 0xFFFFFF, str);
**	free(str);
**}
*/

static t_vector	*cast_ray(t_mlx *mlx, t_vector *origin, t_vector *direction)
{
	if (mlx || origin || direction)
		return (NULL);
	return (NULL);
}

void			render(t_mlx *mlx, t_camera *camera)
{
	t_vector	origin;
	t_vector	*pixel;
	t_vector	*direction;
	float		scale = tan(camera->fov * 0.5 * M_PI / 180);
	float		ratio = (float)WIDTH / (float)HEIGHT;
	float		x;
	float		y;
	t_u32		*buffer = (t_u32 *)mlx->image->buffer;
	t_u32		color;
	int			index;

	ft_bzero(mlx->image->buffer, HEIGHT * mlx->image->line);
	vector_set(&origin, 0, 0, 0);
	for (t_u32 j = 0; j < HEIGHT; ++j)
	for (t_u32 i = 0; i < WIDTH; ++i)
	{
		x =     (2 * (i + 0.5) / (float)WIDTH - 1) * ratio * scale;
		y = (1 - 2 * (j + 0.5) / (float)HEIGHT) * scale;
		direction = vector_new(x, y, -1);
		vector_normalize(direction);
		pixel = cast_ray(mlx, &origin, direction);
		color = color_new(0, pixel->x, pixel->y, pixel->z);
		buffer[index++] = color;
	}
	mlx_put_image_to_window(
		mlx->mlx_ptr,
		mlx->win_ptr,
		mlx->img_ptr, 0, 0);
	//render_debug(mlx, camera, &camera->matrix);
}
