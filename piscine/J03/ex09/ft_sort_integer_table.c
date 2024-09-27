/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_integer_table.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 16:42:17 by aduquesn          #+#    #+#             */
/*   Updated: 2017/09/13 16:40:07 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	swap(int *a, int *b)
{
	int a_num;
	int b_num;

	a_num = *a;
	b_num = *b;
	*a = b_num;
	*b = a_num;
}

void	ft_sort_integer_table(int *tab, int size)
{
	int min;
	int i;
	int j;

	i = 0;
	while (i < size - 1)
	{
		min = i;
		j = i + 1;
		while (j < size)
		{
			if (tab[j] < tab[min])
				min = j;
			j++;
		}
		if (min != i)
		{
			swap(&tab[i], &tab[min]);
		}
		i++;
	}
}
