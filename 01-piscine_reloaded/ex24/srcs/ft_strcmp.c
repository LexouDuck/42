/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:12 by aduquesn          #+#    #+#             */
/*   Updated: 2017/11/30 19:59:18 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_strcmp(const char *str1, const char *str2)
{
	int i;

	if (str1 == str2)
		return (0);
	if (str1 && str2)
	{
		i = 0;
		while (str1[i] && str2[i])
		{
			if (str1[i] != str2[i])
				return (str1[i] - str2[i]);
			i++;
		}
		return (0);
	}
	return ((str1 ? str1[0] : 0) -
			(str2 ? str2[0] : 0));
}
