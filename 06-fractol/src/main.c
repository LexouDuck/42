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

#include "../fractol.h"

static int	fractol_init(t_fractol *fractol, char *arg)
{
	if (fractol == NULL)
		return (ERROR);
	else if (ft_strcmp(arg, "julia") == 0)
		fractol->type = julia;
	else if (ft_strcmp(arg, "fatou") == 0)
		fractol->type = fatou;
	else if (ft_strcmp(arg, "mandelbrot") == 0)
		fractol->type = mandelbrot;
	fractol->radius = 1.8;
	fractol->zoom = 2.0;
	fractol->anchor.x = WIN_W / 2.0;
	fractol->anchor.y = WIN_H / 2.0;
	fractol->mouse.x = WIN_W / 2;
	fractol->mouse.y = 0;
	return (OK);
}

static int	img_init(t_mlx *mlx)
{
	t_image	*image;

	if (!(image = (t_image *)malloc(sizeof(t_image))))
		return (ERROR);
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_W, WIN_H);
	image->buffer = (t_u8 *)mlx_get_data_addr(mlx->img_ptr,
		&(image->bpp),
		&(image->line),
		&(image->endian));
	mlx->image = image;
	return (OK);
}

static int	open_window(t_fractol *fractol, char *title)
{
	t_mlx	mlx;

	mlx.fractol = fractol;
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
	if (!(mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIN_W, WIN_H, title)))
	{
		ft_putendl("Error: could not open new window");
		return (ERROR);
	}
	setup_events(&mlx);
	render(&mlx);
	mlx_loop(mlx.mlx_ptr);
	return (OK);
}

int			main(int argc, char **argv)
{
	t_fractol	fractol;

	if (argc == 2)
	{
		if (fractol_init(&fractol, argv[1]) == ERROR)
			return (ERROR);
		if (open_window(&fractol, ft_strjoin("Fractol - ", argv[1])))
			return (ERROR);
		return (OK);
	}
	ft_putendl("fractol: expecting one argument among the following:"
		"\n - julia\n - fatou\n - mandelbrot");
	return (ERROR);
}
