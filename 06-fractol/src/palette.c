/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"
#include <time.h>

t_channel	palette_set_channel(
	int			center,
	int			amplitude,
	double		phase,
	double		frequency)
{
	t_channel	result;

	result.center = center;
	result.amplitude = amplitude;
	result.phase = phase;
	result.frequency = frequency;
	return (result);
}

static void	palette_randomize(t_palette *palette)
{
	time_t	t;

	srand((unsigned)time(&t));
	palette->r.center = rand() % 256;
	palette->r.amplitude = rand() % (256 - palette->r.center);
	palette->r.phase = (double)(rand() % 360) * M_PI / 180;
	palette->r.frequency = (double)(rand() % 80) / 1000.0 + 0.1;
	palette->g.center = rand() % 256;
	palette->g.amplitude = rand() % (256 - palette->g.center);
	palette->g.phase = (double)(rand() % 360) * M_PI / 180;
	palette->g.frequency = (double)(rand() % 80) / 1000.0 + 0.1;
	palette->b.center = rand() % 256;
	palette->b.amplitude = rand() % (256 - palette->b.center);
	palette->b.phase = (double)(rand() % 360) * M_PI / 180;
	palette->b.frequency = (double)(rand() % 80) / 1000.0 + 0.1;
}

int			event_key_palette(t_mlx *mlx, int key)
{
	if (key == KEY_NUMPAD_ENTER)
		palette_randomize(&mlx->fractol->palette);
	else if (key == KEY_NUMPAD_1)
		mlx->fractol->palette.r.center += 20;
	else if (key == KEY_NUMPAD_2)
		mlx->fractol->palette.r.amplitude += 2;
	else if (key == KEY_NUMPAD_3)
		mlx->fractol->palette.r.frequency += 0.01;
	else if (key == KEY_NUMPAD_4)
		mlx->fractol->palette.g.center += 20;
	else if (key == KEY_NUMPAD_5)
		mlx->fractol->palette.g.amplitude += 20;
	else if (key == KEY_NUMPAD_6)
		mlx->fractol->palette.g.frequency += 20;
	else if (key == KEY_NUMPAD_7)
		mlx->fractol->palette.b.center += 20;
	else if (key == KEY_NUMPAD_8)
		mlx->fractol->palette.b.amplitude += 2;
	else if (key == KEY_NUMPAD_9)
		mlx->fractol->palette.b.frequency += 0.01;
	else
		return (1);
	return (0);
}
