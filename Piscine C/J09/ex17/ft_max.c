/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 14:54:16 by aduquesn          #+#    #+#             */
/*   Updated: 2017/09/08 14:54:40 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_max(int *tab, int length);

int		ft_max(int *tab, int length)
{
	int		i;
	int		j;

	i = 0;
	j = tab[i];
	while (i < length)
	{
		if (j < tab[i])
			j = tab[i];
		i++;
	}
	return (j);
}
