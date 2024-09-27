/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_collatz_conjecture.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 14:08:08 by aduquesn          #+#    #+#             */
/*   Updated: 2017/09/08 14:34:04 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void			recursive_collatz(unsigned int base, unsigned int *n)
{
	(*n)++;
	if (base > 1431655764 && base % 2 == 1)
	{
		*n = 0;
		return ;
	}
	if (base == 1)
		return ;
	if (base % 2 == 0)
		recursive_collatz(base / 2, n);
	else
		recursive_collatz(3 * base + 1, n);
}

unsigned int	ft_collatz_conjecture(unsigned int base)
{
	unsigned int n;

	n = 0;
	recursive_collatz(base, &n);
	return (n - 1);
}
