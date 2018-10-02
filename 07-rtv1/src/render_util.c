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

void		render_debug(void *mlx, void *win, t_camera *camera)
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

void	get_camera_matrix(t_camera *camera)
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

void	set_ray_to_object_space(t_ray *ray, t_object *object)
{
	t_vector	scale;

	vector_set(&ray->orig,
		object->position.x - ray->orig.x,
		object->position.y - ray->orig.y,
		object->position.z - ray->orig.z);
	vector_transform(&ray->orig, &object->matrix);
	scale.x = 1 / object->scale.x;
	scale.y = 1 / object->scale.y;
	scale.z = 1 / object->scale.z;
	ray->orig.x *= scale.x;
	ray->orig.y *= scale.y;
	ray->orig.z *= scale.z;
	vector_transform(&ray->dir, &object->matrix);
	ray->dir.x *= scale.x;
	ray->dir.y *= scale.y;
	ray->dir.z *= scale.z;
}
