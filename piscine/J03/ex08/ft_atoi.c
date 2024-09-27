/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 18:43:23 by aduquesn          #+#    #+#             */
/*   Updated: 2017/09/12 13:47:16 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	get_offset(char *str);

int	get_result(char *str, int offset, int length);

int	is_zero_char(char c)
{
	return (('A' <= c && c <= 'Z') ||
			('a' <= c && c <= 'z') ||
			('!' <= c && c <= '*') ||
			c == ',' ||
			c == '.' ||
			c == '/');
}

int	ft_atoi(char *str)
{
	int offset;
	int neg;
	int i;

	offset = get_offset(str);
	if (offset < 0)
	{
		neg = -1;
		offset *= -1;
	}
	else
		neg = 1;
	i = 0;
	while (str[offset + i] >= '0' && str[offset + i] <= '9')
		i++;
	return (get_result(str, offset, i) * neg);
}

int	get_offset(char *str)
{
	int i;

	i = 0;
	while (str[i] < '0' || str[i] > '9')
	{
		if (is_zero_char(str[i]))
			return (0);
		else if (str[i] == '-')
		{
			i++;
			return (i * -1);
		}
		else if (str[i] == '+')
		{
			i++;
			return (i);
		}
		i++;
	}
	return (i);
}

int	get_result(char *str, int offset, int length)
{
	int result;
	int digit;
	int i;
	int j;

	result = 0;
	digit = 1;
	i = 0;
	j = 0;
	while (i < length)
	{
		while (j < i)
		{
			digit *= 10;
			j++;
		}
		result += (str[offset + length - 1 - i] - '0') * digit;
		i++;
	}
	return (result);
}
