/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 19:49:10 by aduquesn          #+#    #+#             */
/*   Updated: 2017/09/12 17:19:29 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(char *str, char *to_find)
{
	int length;
	int match;
	int i;

	length = 0;
	while (to_find[length])
		length++;
	i = 0;
	while (str[i])
	{
		match = 0;
		while (match < length)
		{
			if (str[i + match] == to_find[match])
				match++;
			else
				break ;
		}
		if (match == length)
			return (str + i);
		i++;
	}
	return (0);
}
