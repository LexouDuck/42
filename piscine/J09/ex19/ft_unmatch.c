/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unmatch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 12:14:38 by aduquesn          #+#    #+#             */
/*   Updated: 2017/09/08 16:07:59 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_unmatch(int *tab, int length);

void	get_match(int match[], int *tab, int length);

int		ft_unmatch(int *tab, int length)
{
	int match[length];
	int i;

	i = 0;
	while (i < length)
	{
		match[i++] = 0;
	}
	get_match(match, tab, length);
	i = 0;
	while (i < length)
	{
		if (match[i] == 0)
			return (tab[i]);
		i++;
	}
	return (0);
}

void	get_match(int *match, int *tab, int length)
{
	int i;
	int j;

	i = 0;
	while (i < length - 1)
	{
		j = i + 1;
		while (j < length)
		{
			if (!match[i] && !match[j] && tab[i] == tab[j])
			{
				match[i] = 1;
				match[j] = 1;
				j = length;
				break ;
			}
			j++;
		}
		i++;
	}
}
