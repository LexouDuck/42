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
	if (mlx == NULL)
		return (ERROR);
	return (OK);
}

static int	event_mouse_release(int button, int x, int y, void *param)
{
ft_putstr("MOUSE RELEASED:");
ft_putstr(ft_itoa_hex((t_u32)button, "0x"));
ft_putstr(" | x:"); ft_putstr(ft_itoa(x));
ft_putstr(", y:"); ft_putendl(ft_itoa(y));
	t_mlx		*mlx;

	mlx = (t_mlx *)param;
	if (mlx == NULL)
		return (ERROR);
	if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN)
	{
		mlx->fractol->zoom += (button == MOUSE_SCROLL_UP) ? -0.1 : 0.1;
		render(mlx);
	}
	return (OK);
}

static int	event_mouse_move(int x, int y, void *param)
{
	static int	old_x = 0;
	static int	old_y = 0;
	float		d_x;
	float		d_y;
	t_mlx		*mlx;

	mlx = (t_mlx *)param;
	mlx->fractol->mouse_x = x;
	mlx->fractol->mouse_y = y;
	d_x = (float)(x - old_x) * 0.05;
	d_y = (float)(y - old_y) * 0.05;
	if (d_x || d_y)
		render(mlx);
	old_x = x;
	old_y = y;
	return (OK);
}

static int	event_key(int key, void *param)
{
ft_putstr("KEY PRESSED: ");
ft_putendl(ft_itoa_hex((t_u32)key, "0x"));
	t_mlx		*mlx;

	mlx = (t_mlx *)param;
	if (mlx == NULL)
		return (ERROR);
	if (key == KEY_ESC)
	{
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		exit(OK);
	}
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
