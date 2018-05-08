/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:08 by aduquesn          #+#    #+#             */
/*   Updated: 2017/12/22 04:44:38 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		i;
	long	result;
	int		neg;

	i = 0;
	result = 0;
	neg = 1;
	while (!(ft_isdigit(nptr[i]) || nptr[i] == '+' || nptr[i] == '-'))
	{
		if (nptr[i] == 0 || !ft_isspace(nptr[i]))
			return (0);
		i++;
	}
	if (nptr[i] == '-')
	{
		neg = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] != '\0' && ft_isdigit(nptr[i]))
		result = result * 10 + nptr[i++] - '0';
	return ((int)(result * neg));
}
