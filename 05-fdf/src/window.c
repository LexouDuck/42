/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

inline int	is_in_window(int x, int y)
{
	return (x >= 0 && x < WIDTH &&
			y >= 0 && y < HEIGHT);
}

inline void	bring_into_window(t_point *point)
{
	if (point->x < 0)
		point->x = 0;
	else if (point->x >= WIDTH)
		point->x = WIDTH - 1;
	if (point->y < 0)
		point->y = 0;
	else if (point->y >= HEIGHT)
		point->y = HEIGHT - 1;
}

inline void	set_pixel(t_image *image, t_point *pos)
{
	t_u8	*buffer;
	int		bpp;
	int		index;

	buffer = image->buffer;
	bpp = (image->bpp / 8);
	index = (pos->x * bpp + pos->y * image->line);
	buffer[index++] = color_get_b(pos->color);
	buffer[index++] = color_get_g(pos->color);
	buffer[index++] = color_get_r(pos->color);
}

inline int	get_color_mean(int color1, int color2, float ratio)
{
	int		result;
	int		channel;
	float	tmp;

	result = 0;
	channel = color_get_r(color1);
	tmp = ratio * (float)(color_get_r(color2) - channel);
	result |= ((channel + (int)tmp) & 0xFF) << 16;
	channel = color_get_g(color1);
	tmp = ratio * (float)(color_get_g(color2) - channel);
	result |= ((channel + (int)tmp) & 0xFF) << 8;
	channel = color_get_b(color1);
	tmp = ratio * (float)(color_get_b(color2) - channel);
	result |= ((channel + (int)tmp) & 0xFF);
	return (result);
}
