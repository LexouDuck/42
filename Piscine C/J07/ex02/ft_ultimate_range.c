/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_range.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 16:22:17 by aduquesn          #+#    #+#             */
/*   Updated: 2017/09/14 18:07:40 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_ultimate_range(int **range, int min, int max)
{
	int i;

	if (range == 0)
		return (0);
	if (min >= max)
	{
		*range = 0;
		return (0);
	}
	*range = malloc((max - min) * 4);
	i = min;
	while (i < max)
	{
		*(*range + i - min) = i;
		i++;
	}
	return (max - min);
}
