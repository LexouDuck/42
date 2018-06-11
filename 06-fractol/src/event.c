/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

static int	event_mouse_press(int button, int x, int y, void *param)
{
ft_putstr("MOUSE PRESSED: ");
ft_putstr(ft_itoa_hex((t_u32)button, "0x"));
ft_putstr(" | x:"); ft_putstr(ft_itoa(x));
ft_putstr(", y:"); ft_putendl(ft_itoa(y));
	t_mlx		*mlx;

	mlx = (t_mlx *)param;
	if (button == MOUSE_R_CLICK)
	{
		mlx->fractol->mouse.color = 0;
	}
	else if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN)
	{
		mlx->fractol->zoom *= (button == MOUSE_SCROLL_UP) ? 0.9 : 1.1;
		if (mlx->fractol->zoom > MAX_ZOOM)
			mlx->fractol->zoom = MAX_ZOOM;
		render(mlx);
	}
	return (OK);
}

static int	event_mouse_release(int button, int x, int y, void *param)
{
ft_putstr("MOUSE RELEASED:");
ft_putstr(ft_itoa_hex((t_u32)button, "0x"));
ft_putstr(" | x:"); ft_putstr(ft_itoa(x));
ft_putstr(", y:"); ft_putendl(ft_itoa(y));
	t_mlx		*mlx;
	double		scale;

	mlx = (t_mlx *)param;
	if (button == MOUSE_L_CLICK)
	{
		scale = (mlx->fractol->zoom * mlx->fractol->radius);
		mlx->fractol->anchor.x += scale * (double)(x - WIN_W / 2) / (double)WIN_H;
		mlx->fractol->anchor.y += scale * (double)(y - WIN_H / 2) / (double)WIN_H;
		render(mlx);
	}
	else if (button == MOUSE_R_CLICK)
	{
		mlx->fractol->mouse.color = 0xFFFFFF;
		render(mlx);
	}
	return (OK);
}

static int	event_mouse_move(int x, int y, void *param)
{
	static int	old_x = 0;
	static int	old_y = 0;
	double		d_x;
	double		d_y;
	t_mlx		*mlx;

	mlx = (t_mlx *)param;
	d_x = (double)(x - old_x) * 1.0;
	d_y = (double)(y - old_y) * 1.0;
	if (mlx->fractol->mouse.color)
	{
		mlx->fractol->mouse.x = x;
		mlx->fractol->mouse.y = y;
		if ((mlx->fractol->type == julia || mlx->fractol->type == fatou)
			&& (d_x || d_y))
			render(mlx);
	}
	old_x = x;
	old_y = y;
	return (OK);
}

static int	event_key(int key, void *param)
{
ft_putstr("KEY PRESSED: ");
ft_putendl(ft_itoa_hex((t_u32)key, "0x"));
	t_mlx		*mlx;
	int			tmp;
	double		d;

	mlx = (t_mlx *)param;
	d = mlx->fractol->zoom;
	if (key == KEY_ESC)
	{
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		exit(OK);
	}
	else if ((tmp = key == KEY_LEFT) || key == KEY_RIGHT)
		mlx->fractol->anchor.x += tmp ? -d : d;
	else if ((tmp = key == KEY_UP) || key == KEY_DOWN)
		mlx->fractol->anchor.y += tmp ? -d : d;
	else if ((tmp = key == KEY_PAGE_UP) || key == KEY_PAGE_DN)
		mlx->fractol->radius *= tmp ? 0.9 : 1.1;
	else if (event_key_palette(mlx, key))
		return (OK);
	render(mlx);
	return (OK);
}

int			setup_events(t_mlx *mlx)
{
	int event;
	int	mask;

	mlx_key_hook(mlx->win_ptr, event_key, mlx);
	mask = 0;
	mask |= MASK_POINTERMOTION;
	mask |= MASK_BUTTON1MOTION;
	mask |= MASK_BUTTON2MOTION;
	mask |= MASK_BUTTON3MOTION;
	event = EVENT_MOTIONNOTIFY;
	mlx_hook(mlx->win_ptr, event, mask, event_mouse_move, mlx);
	mask = MASK_BUTTONPRESS;
	event = EVENT_BUTTONPRESS;
	mlx_hook(mlx->win_ptr, event, mask, event_mouse_press, mlx);
	mask = MASK_BUTTONRELEASE;
	event = EVENT_BUTTONRELEASE;
	mlx_hook(mlx->win_ptr, event, mask, event_mouse_release, mlx);
	return (OK);
}
