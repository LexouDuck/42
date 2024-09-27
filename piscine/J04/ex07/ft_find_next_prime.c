/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_next_prime.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 15:01:19 by aduquesn          #+#    #+#             */
/*   Updated: 2017/09/12 21:15:49 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_find_next_prime(int nb)
{
	int result;
	int i;

	result = (nb < 2) ? 2 : nb;
	while (result < 2147483647)
	{
		i = 2;
		while (i < result)
		{
			if (result % i == 0)
				break ;
			i++;
		}
		if (i == result)
			return (result);
		result++;
	}
	return (0);
}
