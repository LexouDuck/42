/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 22:01:41 by aduquesn          #+#    #+#             */
/*   Updated: 2017/09/14 16:23:37 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(char *src)
{
	char *str;
	int i;

	if (src == 0)
		return (src);
	i = 0;
	while (src[i])
		i++;
	str = malloc(i);
	i = 0;
	while (src[i])
	{
		str[i] = src[i];
		i++;
	}
	return (str);
}
