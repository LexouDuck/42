/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 17:11:36 by aduquesn          #+#    #+#             */
/*   Updated: 2017/11/30 16:34:03 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iterative_factorial(int nb)
{
	int result;
	int i;

	if (nb == 0 || nb == 1)
		return (1);
	else if (nb < 0 || nb > 12)
		return (0);
	result = 1;
	i = nb;
	while (i > 0)
	{
		result *= i--;
	}
	return (result);
}
