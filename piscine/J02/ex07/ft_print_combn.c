/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_combn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 19:22:52 by aduquesn          #+#    #+#             */
/*   Updated: 2017/09/14 14:36:33 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_putchar(char c);

void	print_chars(int *digits, int num[])
{
	int i;
	int check_end;

	i = *digits;
	while (i--)
	{
		ft_putchar(num[i] - 1 + '0');
	}
	i = 0;
	check_end = 0;
	while (i < *digits)
	{
		if (num[i] != 10 - i)
			check_end = 1;
		i++;
	}
	if (check_end)
	{
		ft_putchar(',');
		ft_putchar(' ');
	}
}

void	recursive(int *digits, int n, int num[])
{
	if (n >= 0)
	{
		num[n] = num[n + 1] + 1;
		while (num[n] <= 10 - n)
		{
			recursive(digits, n - 1, num);
			num[n]++;
		}
	}
	else
	{
		print_chars(digits, num);
	}
}

void	ft_print_combn(int n)
{
	int num[n];

	num[n] = 0;
	recursive(&n, n - 1, num);
}
