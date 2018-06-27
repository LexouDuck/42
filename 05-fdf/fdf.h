/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FDF_H
# define __FDF_H

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

# include <mlx.h>
# include "../mlx_events.h"
# include "libft/libft.h"

int				get_next_line(const int fd, char **line);

# define ALT	0.1

# define WIDTH	512
# define HEIGHT	512

typedef struct	s_point
{
	int			x;
	int			y;
	int			color;
}				t_point;

typedef struct	s_rect
{
	int			x;
	int			y;
	int			width;
	int			height;
}				t_rect;

typedef struct	s_vector
{
	float		x;
	float		y;
	float		z;
}				t_vector;

typedef struct	s_matrix
{
	t_vector	*u;
	t_vector	*v;
	t_vector	*w;
	t_vector	*t;
}				t_matrix;

typedef struct	s_vertex
{
	int			display;
	t_vector	absolute;
	t_vector	projected;
}				t_vertex;

typedef struct	s_edge
{
	t_vertex	*vertex1;
	t_vertex	*vertex2;
}				t_edge;

typedef struct	s_face
{
	t_edge		*edge1;
	t_edge		*edge2;
	t_edge		*edge3;
}				t_face;

typedef struct	s_space
{
	t_list		*vertices;
	t_list		*edges;
	t_list		*faces;
}				t_space;

typedef struct	s_camera
{
	int			mode;
	int			render;
	int			fov;
	t_vector	anchor;
	t_vector	pos;
	float		lat;
	float		lon;
	float		zoom;
	float		angle;
	t_vector	tilt;
	float		range_min;
	float		range_max;
	t_matrix	matrix;
}				t_camera;

typedef struct	s_fdf
{
	char		**map;
	t_u32		map_width;
	t_u32		map_height;
	t_camera	*camera;
	t_space		*space;
}				t_fdf;

typedef	struct	s_image
{
	int			bpp;
	int			line;
	int			endian;
	t_u8		*buffer;
}				t_image;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	t_image		*image;
	t_fdf		*fdf;
}				t_mlx;

/*
**	====	space_add.c
*/
t_vertex		*add_vertex(t_space *space, float x, float y, float z);
t_edge			*add_edge(t_space *space, t_vertex *v1, t_vertex *v2);
t_face			*add_face(t_space *space, t_edge *e1, t_edge *e2, t_edge *e3);

/*
**	====	space_get.c
*/
t_vertex		*get_vertex(t_space *space, float x, float y, float z);
t_edge			*get_edge(t_space *space, t_vertex *v1, t_vertex *v2);
t_face			*get_face(t_space *space, t_edge *e1, t_edge *e2, t_edge *e3);

/*
**	====	space_fdf.c
*/
int				fdf_readmap(t_fdf *fdf, int fd);
int				fdf_getmap_verts(t_fdf *fdf);
int				fdf_getmap_edges(t_fdf *fdf);

/*
**	====	draw_line.c
*/

void			draw_line(t_mlx	*mlx, t_point *pos1, t_point *pos2);

/*
**	====	draw_rectangle.c
*/
void			draw_rectangle(t_mlx *mlx, t_rect *rectangle, int color);
void			fill_rectangle(t_mlx *mlx, t_rect *rectangle, int color);

/*
**	====	color.c
*/
t_u32			color_new(t_u8 a, t_u8 r, t_u8 g, t_u8 b);
t_u8			color_get_a(t_u32 color);
t_u8			color_get_r(t_u32 color);
t_u8			color_get_g(t_u32 color);
t_u8			color_get_b(t_u32 color);

/*
**	====	window.c
*/
int				is_in_window(int x, int y);
void			bring_into_window(t_point *point);
void			set_pixel(t_image *image, t_point *pos);
t_u32			get_color_mean(t_u32 color1, t_u32 color2, float ratio);

/*
**	====	vector.c
*/
t_vector		*vector_new(float x, float y, float z);
void			vector_set(t_vector *vector, float x, float y, float z);
float			vector_length(t_vector const *vector);
void			vector_scale(t_vector *vector, float scale);
char			*vector_tostr(t_vector *vector, int precision);

/*
**	====	vector_op.c
*/
void			vector_invert(t_vector *vector);
void			vector_normalize(t_vector *vector);
float			vector_scalar(t_vector *v1, t_vector *v2);
t_vector		*vector_multiply(t_vector *v1, t_vector *v2);
void			vector_transform(t_vector *vector, t_matrix *matrix);

/*
**	====	matrix.c
*/
t_matrix		*matrix_new(
	t_vector *u, t_vector *v, t_vector *w, t_vector *t);
void			matrix_set(t_matrix *result,
	t_vector *u, t_vector *v, t_vector *w);
void			matrix_transpose(t_matrix *matrix);
void			matrix_inverse(t_matrix *matrix);
t_matrix		*matrix_multiply(t_matrix *m1, t_matrix *m2);

/*
**	====	camera.c
*/
t_camera		*camera_new(t_fdf *fdf);
void			camera_pan(t_camera *camera, float x, float y);
void			camera_rotate(t_camera *camera, float x, float y);
void			camera_zoom_tilt(t_camera *camera, float x, float y);
void			camera_update(t_camera *camera);

/*
**	====	projection.c
*/
void			get_camera_matrix(t_camera *camera);
void			project_vertices(t_mlx *mlx,
	t_matrix *camera_matrix,
	t_camera *camera);

/*
**	====	render.c
*/
void			render(t_mlx *mlx, t_camera *camera);

/*
**	====	event.c
*/
int				setup_events(t_mlx *mlx);

/*
** === CAMERA MODES ===
*/
# define CAMERA_NONE		0
# define CAMERA_ROTATE		1
# define CAMERA_ZOOM		2
# define CAMERA_PAN			3

/*
** === RENDERING MODES ===
*/
# define RENDER_EDGE_PERSP	0
# define RENDER_EDGE_ORTHO	1
# define RENDER_VERT_PERSP	2
# define RENDER_VERT_ORTHO	3

#endif
