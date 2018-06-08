/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

inline char	color_get_a(int color)
{
	return ((char)((color >> 24) & 0xFF));
}

inline t_u8	color_get_r(int color)
{
	return ((t_u8)((color >> 16) & 0xFF));
}

inline t_u8	color_get_g(int color)
{
	return ((t_u8)((color >> 8) & 0xFF));
}

inline t_u8	color_get_b(int color)
{
	return ((t_u8)(color & 0xFF));
}

inline int	color_new(char a, t_u8 r, t_u8 g, t_u8 b)
{
	return ((a << 24) | (r << 16) | (g << 8) | b);
}
