/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 22:03:52 by aduquesn          #+#    #+#             */
/*   Updated: 2017/09/14 16:24:07 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	*ft_range(int min, int max)
{
	int *result;
	int i;

	result = malloc((max - min) * 4);
	i = min;
	while (i < max)
	{
		result[i - min] = i;
		i++;
	}
	return (result);
}
