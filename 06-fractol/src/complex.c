/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

inline void	complex_add(t_complex *result,
	t_complex const c1,
	t_complex const c2)
{
	result->x = (c1.x + c2.x);
	result->y = (c1.y + c2.y);
}

inline void	complex_sub(t_complex *result,
	t_complex const c1,
	t_complex const c2)
{
	result->x = (c1.x - c2.x);
	result->y = (c1.y - c2.y);
}

inline void	complex_mul(t_complex *result,
	t_complex const c1,
	t_complex const c2)
{
	result->x = (c1.x * c2.x) - (c1.y * c2.y);
	result->y = (c1.x * c2.y) + (c1.y * c2.x);
}

inline void	complex_div(t_complex *result,
	t_complex const c1,
	t_complex const c2)
{
	double	tmp;

	tmp = 1.0 / (c2.x * c2.x + c2.y * c2.y);
	result->x = (c1.x * c2.x + c1.y * c2.y) * tmp;
	result->y = (c1.y * c2.x - c1.x * c2.y) * tmp;
}

void		complex_pow(t_complex *result,
	t_complex const c,
	int n)
{
	t_complex tmp;

	if (n <= 0)
	{
		result->x = 1;
		result->y = 0;
	}
	else if (n == 1)
	{
		result->x = c.x;
		result->y = c.y;
	}
	else
	{
		complex_mul(result, c, c);
		--n;
		while (--n)
		{
			tmp.x = result->x;
			tmp.y = result->y;
			complex_mul(result, tmp, c);
		}
	}
}
