/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 20:31:22 by exam              #+#    #+#             */
/*   Updated: 2017/09/08 21:05:02 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char *ft_itoa_base(int value, int base);

char *ft_itoa_base(int value, int base)
{
	char *digits[1024];
	int length;
	int digit;
	int i = 0;

	while (value > 0)
	{
		digits[i] = malloc(1);
		*digits[i] = value % base;
		value /= base;
		i++;
	}
	length = i;
	char *result = malloc(length);
	while (i--)
	{
		digit = *digits[length - 1 - i];
		if (digit < 10) result[i] = digit + '0';
		else result[i] = digit + 55;
	}
	return result;
}
