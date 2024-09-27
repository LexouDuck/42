/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_strings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 17:55:35 by tduquesn          #+#    #+#             */
/*   Updated: 2017/09/20 21:51:40 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		ft_strcmp(char *s1, char *s2)
{
	unsigned char	c1;
	unsigned char	c2;
	int				i;

	i = 0;
	while (s1[i] == s2[i] && s1[i])
		i++;
	c1 = s1[i];
	c2 = s2[i];
	return (c1 - c2);
}

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	while (i <= n)
		dest[i++] = '\0';
	return (dest);
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	len;

	len = 0;
	while (*(dest + len))
		len++;
	i = 0;
	while (*(src + i))
	{
		*(dest + len + i) = *(src + i);
		i++;
	}
	*(dest + len + i) = '\0';
	return (dest);
}

char	*ft_strncat(char *dest, char *src, int nb)
{
	int length;
	int i;

	length = 0;
	while (dest[length])
		length++;
	i = 0;
	while (i < nb)
	{
		dest[length + i] = src[i];
		i++;
	}
	dest[length + i] = '\0';
	return (dest);
}
