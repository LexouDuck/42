/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 20:33:26 by exam              #+#    #+#             */
/*   Updated: 2017/09/15 20:53:43 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char *ft_itoa(int nbr)
{
	int digits[10];
	char *result;
	long n;
	int i;

	if (nbr == 0)
	{
		result = malloc(1);
		*result = '0';
	}
	else
	{
		n = nbr;
		if (nbr < 0)
			n *= -1;
		i = 0;
		while (n > 0)
		{
			digits[i++] = n % 10;
			n /= 10;
		}
		n = 0;
		if (nbr < 0)
		{
			result = malloc(i + 1);
			result[n++] = '-';
		}
		else result = malloc(i);

		while (i--)
		{
			result[n++] = '0' + digits[i];
		}
	}
	return (result);
}
