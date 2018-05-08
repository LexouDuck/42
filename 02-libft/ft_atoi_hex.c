/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:08 by aduquesn          #+#    #+#             */
/*   Updated: 2017/12/22 04:41:59 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_atoi_hex_is_hex_char(char c)
{
	return (('0' <= c && c <= '9') ||
			('A' <= c && c <= 'F') ||
			('a' <= c && c <= 'f') ||
			c == 'x' || c == 'X');
}

static int	ft_atoi_hex_is_invalid_char(char c)
{
	return (('G' <= c && c <= 'Z' && c != 'X') ||
			('g' <= c && c <= 'z' && c != 'x') ||
			('!' <= c && c <= '*') ||
			c == ',' ||
			c == '.' ||
			c == '/');
}

static int	ft_atoi_hex_get_offset(char const *str)
{
	int i;

	i = 0;
	while (str[i] && !(ft_atoi_hex_is_hex_char(str[i])))
	{
		if (ft_atoi_hex_is_invalid_char(str[i]))
			return (0);
		else if (str[i] == '-')
		{
			i += 1;
			return (i * -1);
		}
		else if (str[i] == '+')
		{
			i += 1;
			return (i);
		}
		++i;
	}
	return (i);
}

static int	ft_atoi_hex_get_result(char const *str, int offset, int length)
{
	int	result;
	int	digit_n;
	int	digit;
	int	i;
	int	j;

	result = 0;
	digit_n = 1;
	i = -1;
	j = 0;
	while (++i < length)
	{
		while (j++ < i)
			digit_n *= 16;
		digit = str[offset + length - 1 - i];
		if ('0' <= digit && digit <= '9')
			digit -= '0';
		else if ('A' <= digit && digit <= 'F')
			digit -= 'A';
		else if ('a' <= digit && digit <= 'f')
			digit -= 'a';
		result += (digit * digit_n);
	}
	return (result);
}

int			ft_atoi_hex(char const *str)
{
	int	offset;
	int	length;
	int	negative;

	if (str == NULL)
		return (0);
	offset = ft_atoi_hex_get_offset(str);
	negative = (offset < 0) ? -1 : 1;
	if (offset < 0)
		offset *= -1;
	if (ft_atoi_hex_is_invalid_char(str[offset]))
		return (0);
	length = 0;
	while (str[offset + length] &&
	ft_atoi_hex_is_hex_char(str[offset + length]))
		length++;
	if (str[offset] == '0' &&
		(str[offset + 1] == 'x' || str[offset + 1] == 'X'))
	{
		offset += 2;
		length -= 2;
	}
	return (length == 0 ? 0 :
		(ft_atoi_hex_get_result(str, offset, length) * negative));
}
