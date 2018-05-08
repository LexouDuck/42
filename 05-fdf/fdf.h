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

// REMOVE THIS BEFORE UPLOAD
#include <stdio.h>

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

# include <mlx.h>

# include "libft/libft.h"

int			get_next_line(const int fd, char **line);

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

typedef struct	s_frustum
{
	float		n;
	float		f;
	float		t;
	float		b;
	float		l;
	float		r;
}				t_frustum;

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
**	====	draw_line.c
*/

void		draw_line(t_mlx	*mlx, t_point *pos1, t_point *pos2);

/*
**	====	draw_rectangle.c
*/
void		draw_rectangle(t_mlx *mlx, t_rect *rectangle, int color);
void		fill_rectangle(t_mlx *mlx, t_rect *rectangle, int color);

/*
**	====	color.c
*/
int			color_new(char a, t_u8 r, t_u8 g, t_u8 b);
char		color_get_a(int color);
t_u8		color_get_r(int color);
t_u8		color_get_g(int color);
t_u8		color_get_b(int color);

/*
**	====	window.c
*/
int			is_in_window(int x, int y);
void		bring_into_window(t_point *point);
void		set_pixel(t_image *image, t_point *pos);
int			get_color_mean(int color1, int color2, float ratio);

/*
**	====	space_add.c
*/
t_vertex	*add_vertex(t_space *space, float x, float y, float z);
t_edge		*add_edge(t_space *space, t_vertex *v1, t_vertex *v2);
t_face		*add_face(t_space *space, t_edge *e1, t_edge *e2, t_edge *e3);

/*
**	====	space_get.c
*/
t_vertex	*get_vertex(t_space *space, float x, float y, float z);
t_edge		*get_edge(t_space *space, t_vertex *v1, t_vertex *v2);
t_face		*get_face(t_space *space, t_edge *e1, t_edge *e2, t_edge *e3);

/*
**	====	space_fdf.c
*/
int			fdf_readmap(t_fdf *fdf, int fd);
int			fdf_getmap_verts(t_fdf *fdf);
int			fdf_getmap_edges(t_fdf *fdf);

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
t_camera	*camera_new(t_fdf *fdf);
void		camera_pan(t_camera *camera, float x, float y);
void		camera_rotate(t_camera *camera, float x, float y);
void		camera_zoom_tilt(t_camera *camera, float x, float y);
void		camera_update(t_camera *camera);

/*
**	====	projection.c
*/
void		get_camera_matrix(t_camera *camera);
void		project_vertices(t_mlx *mlx,
	t_matrix *camera_matrix,
	t_camera *camera);

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

/*
** === MOUSE BUTTONS ===
*/
# ifdef __APPLE__

#  define MOUSE_L_CLICK		3
#  define MOUSE_M_CLICK		1
#  define MOUSE_R_CLICK		2
#  define MOUSE_SCROLL_UP	4
#  define MOUSE_SCROLL_DOWN	5

# else

#  define MOUSE_L_CLICK		1
#  define MOUSE_M_CLICK		2
#  define MOUSE_R_CLICK		3
#  define MOUSE_SCROLL_UP	4
#  define MOUSE_SCROLL_DOWN	5

# endif

/*
** === KEYBOARD BUTTONS ===
*/
# ifdef __APPLE__

#  define KEY_ESC		0x35

#  define KEY_HELP		0x72
#  define KEY_HOME		0x73
#  define KEY_PAGE_UP	0x74
#  define KEY_DELETE	0x75

#  define KEY_EOL		0x77

#  define KEY_PAGE_DOWN 0x79

#  define KEY_LEFT		0x7B
#  define KEY_RIGHT		0x7C
#  define KEY_DOWN		0x7D
#  define KEY_UP		0x7E

# else

#  define KEY_ESC		0xFF1B

#  define KEY_HOME		0xFF50
#  define KEY_LEFT		0xFF51
#  define KEY_UP		0xFF52
#  define KEY_RIGHT		0xFF53
#  define KEY_DOWN		0xFF54
#  define KEY_PREV		0xFF55
#  define KEY_PAGE_UP	0xFF55
#  define KEY_NEXT		0xFF56
#  define KEY_PAGE_DOWN	0xFF56
#  define KEY_EOL		0xFF57
#  define KEY_BOL		0xFF58

#  define KEY_DELETE		0xFF63

# endif

/*
** === EVENT DEFINES ===
*/
# define EVENT_KEYPRESS				2
# define EVENT_KEYRELEASE			3
# define EVENT_BUTTONPRESS			4
# define EVENT_BUTTONRELEASE		5
# define EVENT_MOTIONNOTIFY			6
# define EVENT_ENTERNOTIFY			7
# define EVENT_LEAVENOTIFY			8
# define EVENT_FOCUSIN				9
# define EVENT_FOCUSOUT				10
# define EVENT_KEYMAPNOTIFY			11
# define EVENT_EXPOSE				12
# define EVENT_GRAPHICSEXPOSE		13
# define EVENT_NOEXPOSE				14
# define EVENT_VISIBILITYNOTIFY		15
# define EVENT_CREATENOTIFY			16
# define EVENT_DESTROYNOTIFY		17
# define EVENT_UNMAPNOTIFY			18
# define EVENT_MAPNOTIFY			19
# define EVENT_MAPREQUEST			20
# define EVENT_REPARENTNOTIFY		21
# define EVENT_CONFIGURENOTIFY		22
# define EVENT_CONFIGUREREQUEST		23
# define EVENT_GRAVITYNOTIFY		24
# define EVENT_RESIZEREQUEST		25
# define EVENT_CIRCULATENOTIFY		26
# define EVENT_CIRCULATEREQUEST		27
# define EVENT_PROPERTYNOTIFY		28
# define EVENT_SELECTIONCLEAR		29
# define EVENT_SELECTIONREQUEST		30
# define EVENT_SELECTIONNOTIFY		31
# define EVENT_COLORMAPNOTIFY		32
# define EVENT_CLIENTMESSAGE		33
# define EVENT_MAPPINGNOTIFY		34
# define EVENT_GENERICEVENT			35
# define EVENT_LASTEVENT			36

/*
**	These are the different X event bit-masks for the X-Server.
**	These are not to be confused with event names.
*/
# define MASK_NOEVENT				0L
# define MASK_KEYPRESS				(1L<<0)
# define MASK_KEYRELEASE			(1L<<1)
# define MASK_BUTTONPRESS			(1L<<2)
# define MASK_BUTTONRELEASE			(1L<<3)
# define MASK_ENTERWINDOW			(1L<<4)
# define MASK_LEAVEWINDOW			(1L<<5)
# define MASK_POINTERMOTION			(1L<<6)
# define MASK_POINTERMOTIONHINT		(1L<<7)
# define MASK_BUTTON1MOTION			(1L<<8)
# define MASK_BUTTON2MOTION			(1L<<9)
# define MASK_BUTTON3MOTION			(1L<<10)
# define MASK_BUTTON4MOTION			(1L<<11)
# define MASK_BUTTON5MOTION			(1L<<12)
# define MASK_BUTTONMOTION			(1L<<13)
# define MASK_KEYMAPSTATE			(1L<<14)
# define MASK_EXPOSURE				(1L<<15)
# define MASK_VISIBILITYCHANGE		(1L<<16)
# define MASK_STRUCTURENOTIFY		(1L<<17)
# define MASK_RESIZEREDIRECT		(1L<<18)
# define MASK_SUBSTRUCTURENOTIFY	(1L<<19)
# define MASK_SUBSTRUCTUREREDIRECT	(1L<<20)
# define MASK_FOCUSCHANGE			(1L<<21)
# define MASK_PROPERTYCHANGE		(1L<<22)
# define MASK_COLORMAPCHANGE		(1L<<23)
# define MASK_OWNERGRABBUTTON		(1L<<24)

#endif
