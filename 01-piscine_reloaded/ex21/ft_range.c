/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 22:03:52 by aduquesn          #+#    #+#             */
/*   Updated: 2017/11/30 19:21:40 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	*ft_range(int min, int max)
{
	int *result;
	int i;

	if (min >= max)
		return (0);
	if (!(result = malloc((max - min) * sizeof(int))))
		return (0);
	i = min;
	while (i < max)
	{
		result[i - min] = i;
		i++;
	}
	return (result);
}
