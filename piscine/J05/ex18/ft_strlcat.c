/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 18:19:43 by aduquesn          #+#    #+#             */
/*   Updated: 2017/09/12 19:08:15 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int length;
	unsigned int i;

	length = 0;
	while (dest[length])
		length++;
	i = 0;
	while (length + i < size - 1)
	{
		dest[length + i] = src[i];
		i++;
	}
	dest[length + i] = '\0';
	return (length + i);
}
