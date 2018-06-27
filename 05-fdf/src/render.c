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
			pos.x = ((vertex->projected.x + 1) * 0.5) * WIDTH;
			pos.y = ((vertex->projected.y + 1) * 0.5) * HEIGHT;
			pos.y = (HEIGHT - pos.y);
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
		pos1.x = ((vertex->projected.x + 1) * 0.5) * WIDTH;
		pos1.y = ((vertex->projected.y + 1) * 0.5) * HEIGHT;
		pos1.y = (HEIGHT - pos1.y);
		pos1.color = (render_colors) ? vertex->display : 0xFFFFFF;
		++render;
	}
	if ((vertex = edge->vertex2) && (vertex->display & 0xFF000000))
	{
		pos2.x = ((vertex->projected.x + 1) * 0.5) * WIDTH;
		pos2.y = ((vertex->projected.y + 1) * 0.5) * HEIGHT;
		pos2.y = (HEIGHT - pos2.y);
		pos2.color = (render_colors) ? vertex->display : 0xFFFFFF;
		++render;
	}
	if (render == 2)
		draw_line(mlx, &pos1, &pos2);
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

static void		render_clean(t_matrix *matrix)
{
	free(matrix->u);
	free(matrix->v);
	free(matrix->w);
	free(matrix->t);
}

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
	mlx_put_image_to_window(mlx->mlx_ptr,
							mlx->win_ptr,
							mlx->img_ptr, 0, 0);
	render_debug(mlx->mlx_ptr, mlx->win_ptr, camera);
	render_clean(&camera->matrix);
}
