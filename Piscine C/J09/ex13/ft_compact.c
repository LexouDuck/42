/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compact.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 16:00:58 by aduquesn          #+#    #+#             */
/*   Updated: 2017/09/08 16:01:09 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_compact(char **tab, int length);

int		ft_compact(char **tab, int length)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < length)
	{
		if (tab[i] != 0)
		{
			j++;
		}
		i++;
	}
	return (j);
}
