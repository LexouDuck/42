/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 17:54:00 by tduquesn          #+#    #+#             */
/*   Updated: 2017/09/20 22:31:58 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	**split_map(char *str, char *charset)
{
	int		i;
	int		j;
	int		ws;
	char	**strls;

	if (!(strls = malloc(sizeof(char*) * (count_words(str, charset) + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (i < count_words(str, charset))
	{
		while (is_separator(str[j], charset))
			j++;
		ws = j;
		if (!(strls[i] = (char*)malloc(count_letters(str, ws, charset) + 1)))
			return (NULL);
		while (j < ws + count_letters(str, ws, charset))
		{
			strls[i][j - ws] = str[j];
			j++;
		}
		strls[i++][j - ws] = '\0';
	}
	strls[i] = 0;
	return (strls);
}

int		is_separator(char c, char *charset)
{
	int i;

	i = 0;
	while (charset[i])
		if (c == charset[i++])
			return (1);
	return (0);
}

int		count_words(char *str, char *charset)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (is_separator(str[i], charset))
			i++;
		if (str[i] == '\0')
			return (count);
		count++;
		while (!is_separator(str[i], charset) && str[i])
			i++;
	}
	return (count);
}

int		count_letters(char *str, int ws, char *charset)
{
	int i;

	i = 0;
	while (!is_separator(str[ws + i], charset) && str[ws + i])
		i++;
	return (i);
}
