/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_wstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 21:28:29 by exam              #+#    #+#             */
/*   Updated: 2017/09/15 21:55:10 by exam             ###   ########.fr       */
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
			while (str[i] && !is_separator(str[i]))
			{
				i++;
			}
		}
	}
	return (result);
}

char *string_copy(char *str, int length)
{
	char *result = malloc(length + 1);
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
		while (str[offset] && is_separator(str[offset]))
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

#include <unistd.h>

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		int length = 0;
		char **words = ft_split(argv[1]);
		while (words[length]) length++;

		int word;
		for (int i = length - 1; i >= 0; i--)
		{
			word = 0;
			while (words[i][word]) word++;

			write(1, words[i], word);
			write(1, " ", 1);
		}
	}
	write(1, "\n", 1);
	return (0);
}
