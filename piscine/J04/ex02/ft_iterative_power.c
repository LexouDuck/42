/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 21:04:06 by aduquesn          #+#    #+#             */
/*   Updated: 2017/09/12 13:53:16 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iterative_power(int nb, int power)
{
	int result;
	int i;

	if (power < 0)
		return (0);
	else if (power == 0)
		return (1);
	else if (nb == 0)
		return (0);
	else if (nb == 1)
		return (1);
	else
	{
		result = 1;
		i = 0;
		while (i < power)
		{
			result *= nb;
			i++;
		}
	}
	return (result);
}
