/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RTV1_H
# define __RTV1_H

# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

# include <mlx.h>
# include "../mlx_events.h"
# include "libft/libft.h"

int			get_next_line(int const fd, char **line);
int			read_file(int const fd, char **file);

# define ALT	0.1

# define WIDTH	512
# define HEIGHT	512

typedef struct	s_parser
{
	char		*file;
	int			index;
	int			line;
}				t_parser;

typedef struct	s_point
{
	int			x;
	int			y;
	int			color;
}				t_point;

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

typedef enum	e_geom
{
	none,
	plane,
	triangle,
	sphere,
	cylinder,
	cone,
}				t_geom;

typedef struct	s_object
{
	t_geom		type;
	t_vector	position;
	t_vector	rotation;
	t_vector	scale;
	t_u32		color;
}				t_object;

typedef struct	s_light
{
	t_vector	position;
	float		strength;
	t_u32		color;
}				t_light;

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

typedef struct	s_rtv1
{
	t_camera	*camera;
	t_list		*lights;
	t_list		*objects;
	t_u32		bg_color;
}				t_rtv1;

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
	t_rtv1		*rtv1;
}				t_mlx;

/*
**	====	color.c
*/
int			color_new(char a, t_u8 r, t_u8 g, t_u8 b);
char		color_get_a(int color);
t_u8		color_get_r(int color);
t_u8		color_get_g(int color);
t_u8		color_get_b(int color);

/*
**	====	vector.c
*/
t_vector	*vector_new(float x, float y, float z);
void		vector_set(t_vector *vector, float x, float y, float z);
float		vector_length(t_vector const *vector);
void		vector_scale(t_vector *vector, float scale);
char		*vector_tostr(t_vector *vector);

/*
**	====	vector_op.c
*/
void		vector_invert(t_vector *vector);
void		vector_normalize(t_vector *vector);
float		vector_scalar(t_vector *v1, t_vector *v2);
t_vector	*vector_multiply(t_vector *v1, t_vector *v2);
void		vector_transform(t_vector *vector, t_matrix *matrix);

/*
**	====	matrix.c
*/
t_matrix	*matrix_new(t_vector *u, t_vector *v, t_vector *w, t_vector *t);
void		matrix_set(t_matrix *result, t_vector *u, t_vector *v, t_vector *w);
void		matrix_transpose(t_matrix *matrix);
void		matrix_inverse(t_matrix *matrix);
t_matrix	*matrix_multiply(t_matrix *m1, t_matrix *m2);

/*
**	====	camera.c
*/
t_camera	*camera_new();
void		camera_pan(t_camera *camera, float x, float y);
void		camera_rotate(t_camera *camera, float x, float y);
void		camera_zoom_tilt(t_camera *camera, float x, float y);
void		camera_update(t_camera *camera);

/*
**	====	read.c & read_util.c
*/
char		*rtv1_read_file(t_rtv1 *rtv1, t_parser *parser, int fd);

void		read_whitespace(t_parser *parser);
char		*read_vector_arg(t_parser *parser, t_vector *result);
char		*read_number_arg(t_parser *parser, float *result);
char		*read_color_arg(t_parser *parser, t_u32 *result);

/*
**	====	render.c
*/
void		render(t_mlx *mlx, t_camera *camera);

/*
**	====	event.c
*/
int			setup_events(t_mlx *mlx);

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
