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

#include "../fdf.h"

static void		render_vertices(t_mlx *mlx, int render_colors)
{
	t_point		pos;
	t_list		*lst;
	t_vertex	*vertex;

	lst = mlx->fdf->space->vertices;
	while (lst)
	{
		vertex = (t_vertex *)lst->content;
		if (vertex && (vertex->display & 0xFF000000))
		{
			pos.x =     ((vertex->projected.x + 1) * 0.5) * WIDTH;
			pos.y = (1 - (vertex->projected.y + 1) * 0.5) * HEIGHT;
			pos.color = (render_colors) ? vertex->display : 0xFFFFFF;
			if (is_in_window(pos.x, pos.y))
				set_pixel(mlx->image, &pos);
		}
		lst = lst->next;
	}
}

static void		render_edge(t_mlx *mlx, int render_colors, t_edge *edge)
{
	t_point		pos1;
	t_point		pos2;
	t_vertex	*vertex;
	int			render;

	render = 0;
	if ((vertex = edge->vertex1) && (vertex->display & 0xFF000000)) 
	{
		pos1.x =     ((vertex->projected.x + 1) * 0.5) * WIDTH;
		pos1.y = (1 - (vertex->projected.y + 1) * 0.5) * HEIGHT;
		pos1.color = (render_colors) ? vertex->display : 0xFFFFFF;
		++render;
	}
	if ((vertex = edge->vertex2) && (vertex->display & 0xFF000000))
	{
		pos2.x =     ((vertex->projected.x + 1) * 0.5) * WIDTH;
		pos2.y = (1 - (vertex->projected.y + 1) * 0.5) * HEIGHT;
		pos2.color = (render_colors) ? vertex->display : 0xFFFFFF;
		++render;
	}
	if (render == 2)
		draw_line(mlx, &pos1, &pos2);
}

static void		render_clean(t_matrix *matrix)
{
	free(matrix->u);
	free(matrix->v);
	free(matrix->w);
	free(matrix->t);
}
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
void			render(t_mlx *mlx, t_camera *camera)
{
	int			render_colors;
	t_list		*lst;

	ft_bzero(mlx->image->buffer, HEIGHT * mlx->image->line);
	camera_update(camera);
	get_camera_matrix(camera);
	project_vertices(mlx, &camera->matrix, camera);
	render_colors = (camera->render & 4);
	if (camera->render & 2)
		render_vertices(mlx, render_colors);
	else
	{
		lst = mlx->fdf->space->edges;
		while (lst)
		{
			if (lst->content)
				render_edge(mlx, render_colors, (t_edge *)lst->content);
			lst = lst->next;
		}
	}
	mlx_put_image_to_window(
		mlx->mlx_ptr,
		mlx->win_ptr,
		mlx->img_ptr, 0, 0);
	//render_debug(mlx, camera, &camera->matrix);
	render_clean(&(camera->matrix));
}
