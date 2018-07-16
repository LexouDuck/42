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

#include "../fdf.h"

static int	fdf_init(t_fdf *fdf, int fd)
{
	char	*error;

	if ((error = fdf_readmap(fdf, fd)))
	{
		ft_putendl("Error: the given fdf file is invalid -> returned error:");
		ft_putendl(error);
		return (ERROR);
	}
	if (!(fdf->camera = camera_new(fdf)) ||
		!(fdf->space = (t_space *)malloc(sizeof(t_space))))
	{
		ft_putendl("Error: could not initialize the 3d space");
		return (ERROR);
	}
	if (fdf_getmap_verts(fdf) == ERROR)
	{
		ft_putendl("Error: could not create the vertices for the 3d space");
		return (ERROR);
	}
	if (fdf_getmap_edges(fdf) == ERROR)
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

static int	open_window(t_fdf *fdf, char *title)
{
	t_mlx	mlx;

	mlx.fdf = fdf;
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
	render(&mlx, mlx.fdf->camera);
	setup_events(&mlx);
	mlx_loop(mlx.mlx_ptr);
	return (OK);
}

int			main(int argc, char **argv)
{
	t_fdf	fdf;
	int		fd;
	t_u32	i;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
		{
			ft_putendl("Error: could not open file");
			return (ERROR);
		}
		if (fdf_init(&fdf, fd) == ERROR)
			return (ERROR);
		i = -1;
		while (++i < fdf.map_height)
			free(fdf.map[i]);
		free(fdf.map);
		fdf.map = NULL;
		if (open_window(&fdf, ft_strjoin("FdF - ", argv[1])))
			return (ERROR);
		return (OK);
	}
	ft_putendl("fdf: expecting one file as argument");
	return (ERROR);
}
