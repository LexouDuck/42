/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

static int	rtv1_init(t_rtv1 *rtv1, int fd)
{
	if (rtv1_readmap(rtv1, fd) == ERROR)
	{
		ft_putendl("Error: the given rtv1 file is invalid");
		return (ERROR);
	}
	if (!(rtv1->camera = camera_new(rtv1)) ||
		!(rtv1->space = (t_space *)malloc(sizeof(t_space))))
	{
		ft_putendl("Error: could not initialize the 3d space");
		return (ERROR);
	}
	if (rtv1_getmap_verts(rtv1) == ERROR)
	{
		ft_putendl("Error: could not create the vertices for the 3d space");
		return (ERROR);
	}
	if (rtv1_getmap_edges(rtv1) == ERROR)
	{
		ft_putendl("Error: could not create the edges for the 3d space");
		return (ERROR);
	}
	return (OK);
}

static int	img_init(t_mlx *mlx)
{
	t_image	*image;

	if (!(image = (t_image *)malloc(sizeof(t_image))))
		return (ERROR);
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	image->buffer = (t_u8 *)mlx_get_data_addr(mlx->img_ptr,
		&(image->bpp),
		&(image->line),
		&(image->endian));
	mlx->image = image;
	return (OK);
}

static int	open_window(t_rtv1 *rtv1, char *title)
{
	t_mlx	mlx;

	mlx.rtv1 = rtv1;
	if (!(mlx.mlx_ptr = mlx_init()))
	{
		ft_putendl("Error: could not initialize MinilibX");
		return (ERROR);
	}
	if (img_init(&mlx))
	{
		ft_putendl("Error: could not create render image");
		return (ERROR);
	}
	if (!(mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIDTH, HEIGHT, title)))
	{
		ft_putendl("Error: could not open new window");
		return (ERROR);
	}
	render(&mlx, mlx.rtv1->camera);
	setup_events(&mlx);
	mlx_loop(mlx.mlx_ptr);
	return (OK);
}

int			main(int argc, char **argv)
{
	t_rtv1	rtv1;
	int		fd;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
		{
			ft_putendl("Error: could not open file");
			return (ERROR);
		}
		if (rtv1_init(&rtv1, fd) == ERROR)
			return (ERROR);
		if (open_window(&rtv1, ft_strjoin("FdF - ", argv[1])))
			return (ERROR);
		return (OK);
	}
	ft_putendl("rtv1: expecting one file as argument");
	return (ERROR);
}
