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

static int	init_fractol(t_fractol *fractol, char *arg)
{
	if (fractol == NULL)
		return (ERROR);
	else if (ft_strequ(arg, "julia"))
		fractol->type = julia;
	else if (ft_strequ(arg, "fatou"))
		fractol->type = fatou;
	else if (ft_strequ(arg, "newton"))
		fractol->type = newton;
	else if (ft_strequ(arg, "mandelbrot"))
		fractol->type = mandelbrot;
	else if (ft_strequ(arg, "burningship"))
		fractol->type = burningship;
	else
		return (ERROR);
	fractol->max = 64;
	fractol->zoom = 2.0;
	fractol->radius = 2.0;
	fractol->anchor.x = 0.0;
	fractol->anchor.y = 0.0;
	fractol->mouse.x = WIN_W / 2;
	fractol->mouse.y = 0;
	fractol->mouse.color = 0xFFFFFF;
	return (OK);
}

static void	init_palette(t_fractol *fractol)
{
	if (fractol->type == julia)
	{
		fractol->palette.r = palette_set_channel(150, 99, 1, 0.12);
		fractol->palette.g = palette_set_channel(100, 99, 0, 0.13);
		fractol->palette.b = palette_set_channel(230, 25, 0, 0.16);
	}
	else if (fractol->type == fatou)
	{
		fractol->palette.r = palette_set_channel(0, 128, 0, 0);
		fractol->palette.g = palette_set_channel(200, 1, 0, 0);
		fractol->palette.b = palette_set_channel(0, 16, 0, 0);
	}
	else if (fractol->type == mandelbrot)
	{
		fractol->palette.r = palette_set_channel(100, 99, 0.0, 0.13);
		fractol->palette.g = palette_set_channel(150, 99, 1.0, 0.12);
		fractol->palette.b = palette_set_channel(230, 25, 0.0, 0.16);
	}
	else if (fractol->type == burningship)
	{
		fractol->palette.r = palette_set_channel(230, 25, 0.0, 0.16);
		fractol->palette.g = palette_set_channel(100, 99, 1.0, 0.13);
		fractol->palette.b = palette_set_channel(100, 99, 2.0, 0.10);
	}
}

static int	init_image(t_mlx *mlx)
{
	static void	*functions[5] = {
		&render_julia,
		&render_fatou,
		&render_mandelbrot,
		&render_burningship,
		&render_newton
	};
	t_image		*image;

	if (!(image = (t_image *)malloc(sizeof(t_image))))
		return (ERROR);
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_W, WIN_H);
	image->buffer = (t_u8 *)mlx_get_data_addr(mlx->img_ptr,
		&(image->bpp),
		&(image->line),
		&(image->endian));
	mlx->image = image;
	mlx->mouse = !(mlx->fractol->type == julia || mlx->fractol->type == fatou);
	mlx->render = functions[(int)mlx->fractol->type];
	mlx->rendering = 0;
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
	if (init_image(&mlx))
	{
		ft_putendl("Error: could not create render image");
		return (ERROR);
	}
	if (!(mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIN_W, WIN_H, title)))
	{
		ft_putendl("Error: could not open new window");
		return (ERROR);
	}
	render(&mlx);
	setup_events(&mlx);
	mlx_loop(mlx.mlx_ptr);
	return (OK);
}

int			main(int argc, char **argv)
{
	t_fractol	fractol;

	if (argc == 2)
	{
		if (init_fractol(&fractol, argv[1]) == ERROR)
		{
			ft_putendl("fractol: invalid argument, should be:");
			ft_putendl(" - julia\n - fatou\n - mandelbrot\n - newton");
			return (ERROR);
		}
		srand(time(NULL));
		init_palette(&fractol);
		if (open_window(&fractol, ft_strjoin("Fractol - ", argv[1])))
			return (ERROR);
		return (OK);
	}
	ft_putendl("fractol: expecting one argument among the following:");
	ft_putendl(" - julia\n - fatou\n - mandelbrot\n - burningship\n - newton");
	return (OK);
}
