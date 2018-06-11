/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

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
	vector = vector_new(
		camera->anchor.x + camera->pos.x,
		camera->anchor.y + camera->pos.y,
		camera->anchor.z + camera->pos.z);
	matrix_set(&camera->matrix, axis_right, axis_up, axis_forward);
	vector_set(vector,
		-vector_scalar(vector, axis_right),
		-vector_scalar(vector, axis_up),
		-vector_scalar(vector, axis_forward));
	camera->matrix.t = vector;
	matrix_transpose(&camera->matrix);
}

static inline void	project_vertex(
	t_vertex *vertex,
	t_matrix *camera_matrix,
	float camera_zoom,
	int perspective)
{
	t_vector	*result;
	float		tmp;

	if (vertex == NULL)
		return ;
	result = &vertex->absolute;
	vector_set(&vertex->projected, result->x, result->z, result->y);
	result = &vertex->projected;
	vector_transform(result, camera_matrix);
	tmp = 0;
	if (perspective && result->z < 0)
		tmp = 1 / -result->z;
	else
		tmp = 1 / camera_zoom;
	result->x *= tmp;
	result->y *= tmp;
	if (perspective && result->z >= 0)
		vertex->display &= 0x00FFFFFF;
	else
		vertex->display |= 0xFF000000;
}

void				project_vertices(t_mlx *mlx,
	t_matrix *camera_matrix,
	t_camera *camera)
{
	int			perspective;
	t_list		*lst;

	if (camera_matrix == NULL)
		return ;
	perspective = (camera->render % 2 == 0);
	lst = mlx->fdf->space->vertices;
	while (lst)
	{
		project_vertex((t_vertex *)lst->content,
			camera_matrix,
			camera->zoom,
			perspective);
		lst = lst->next;
	}
}
/*
**t_frustum	*get_camera_bounds(t_camera *camera)
**{
**	t_frustum	*result;
**	float		scale;
**
**	if (!(result = (t_frustum *)malloc(sizeof(t_frustum))))
**		return (NULL);
**	result->n = camera->range_min;
**	result->f = camera->range_max;
**	scale = result->n * tan(camera->fov * 0.5 * M_PI / 180);
**	result->r = ((float)WIDTH / (float)HEIGHT) * scale;
**	result->l = -result->r;
**	result->t = scale;
**	result->b = -result->t;
**	return (result);
**}
**
**t_matrix	*get_projection_matrix_ortho(t_camera *camera)
**{
**	t_frustum	*cam;
**	t_matrix	*result;
**
**	cam = get_camera_bounds(camera);
**	result = matrix_new(
**		vector_new(2 / (cam->r - cam->l), 0, 0),
**		vector_new(0, 2 / (cam->t - cam->b), 0),
**		vector_new(0, 0, 2 / (cam->f - cam->n)),
**		vector_new(
**		 (cam->r + cam->l) / (cam->r - cam->l),
**		 (cam->t + cam->b) / (cam->t - cam->b),
**		-(cam->f + cam->n) / (cam->f - cam->n)));
**	return (result);
**}
**
**t_matrix	*get_projection_matrix_persp(t_camera *camera)
**{
**	t_frustum	*cam;
**	t_matrix	*result;
**
**	cam = get_camera_bounds(camera);
**	result = matrix_new(
**		vector_new(2 * cam->n / (cam->r - cam->l), 0, 0),
**		vector_new(0, 2 * cam->n / (cam->t - cam->b), 0),
**		vector_new(
**		-(cam->r + cam->l) / (cam->r - cam->l),
**		-(cam->t + cam->b) / (cam->t - cam->b),
**		-(cam->f + cam->n) / (cam->f - cam->n)),
**		vector_new(0, 0, -2 * cam->f * cam->n / (cam->f - cam->n)));
**	return (result);
**}
*/
