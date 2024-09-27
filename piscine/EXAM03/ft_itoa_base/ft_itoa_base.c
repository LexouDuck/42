/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 13:23:13 by exam              #+#    #+#             */
/*   Updated: 2017/09/22 14:06:18 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char *ft_itoa_base(int value, int base)
{
	if (base < 2 || 16 < base)
		return (NULL);
	char *result;
	long number = value;
	int i = 0;
	if (value == 0)
	{
		result = malloc(2);
		result[0] = '0';
		result[1] = '\0';
		return (result);
	}
	else while (value != 0)
	{
		value /= base;
		i++;
	}
	result = malloc(i + 1);
	if (number < 0)
	{
		if (base == 10)
		{
			free(result);
			result = malloc(++i + 1);
			result[0] = '-';
		}
		number *= -1;
	}
	result[i--]= '\0';
	while (number > 0)
	{
		result[i] = number % base;
		result[i] += (result[i] < 10) ? '0' : 'A' - 10;
		number /= base;
		i--;
	}
	return (result);
}
