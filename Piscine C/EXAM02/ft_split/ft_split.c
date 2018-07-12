/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 19:47:13 by exam              #+#    #+#             */
/*   Updated: 2017/09/15 20:30:20 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int is_separator(char c)
{
	return (c == ' ' || c == '	' || c == '\n');
}

int get_word_amount(char *str)
{
	int result = 0;
	for (int i = 0; str[i]; i++)
	{
		if (is_separator(str[i]))
			continue;
		else
		{
			result++;
			while (!is_separator(str[i]))
				i++;
		}
	}
	return (result);
}

char *string_copy(char *str, int length)
{
	char *result = malloc(length);
	for	(int i = 0; i < length; i++)
	{
		result[i] = str[i];
	}
	result[length] = '\0';
	return (result);
}

char **ft_split(char *str)
{
	char **result;
	int words;
	int offset;
	int length;
	int i;

	words = get_word_amount(str);
	result = malloc((words + 1) * sizeof(long));
	result[words] = NULL;
	offset = 0;
	i = 0;
	while (i < words)
	{
		while (is_separator(str[offset]))
		{
			offset++;
		}
		length = 0;
		while (str[offset + length])
		{
			if (is_separator(str[offset + length]))
				break;
			length++;
		}
		result[i++] = string_copy(str + offset, length);
		offset += length;
	}
	return (result);
}
