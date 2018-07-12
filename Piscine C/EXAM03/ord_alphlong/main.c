/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 14:44:47 by exam              #+#    #+#             */
/*   Updated: 2017/09/22 16:43:14 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int get_word_amount(char *str)
{
	int result = 0;
	int i = 0;
	while (str[i])
	{
		while  (str[i] == ' ' ||
				str[i] == '	' ||
				str[i] == '\n')
		{
			i++;
		}
		if (str[i])
		{
			result++;
			while  (str[i] &&
					str[i] != ' ' &&
					str[i] != '	' &&
					str[i] != '\n')
			{
				i++;
			}
		}
	}
	return (result);
}

char **get_words(char *str, int amount)
{
	char **result;
	result = malloc((amount + 1) * sizeof(char*));
	if (result == NULL) return (NULL);
	result[amount] = NULL;
	int n = 0;
	int i = 0;
	while (str[i])
	{
		while  (str[i] == ' ' ||
				str[i] == '	' ||
				str[i] == '\n')
		{
			i++;
		}
		if (str[i])
		{
			result[n++] = str + i;
			while  (str[i] &&
					str[i] != ' ' &&
					str[i] != '	' &&
					str[i] != '\n')
			{
				i++;
			}
		}
	}
	return (result);
}

int get_length(char *str)
{
	int length = 0;
	while (str[length] &&
		str[length] != ' ' &&
		str[length] != '	')
		length++;
	str[length] = '\0';
	return (length);
}

int compare(char *s1, char *s2, int length)
{
	int i = 0;
	while (i < length)
	{
		if (s1[i] == s2[i])
			i++;
		else if ('A' <= s1[i] && s1[i] <= 'Z')
		{
			if (s2[i] == s1[i] + 32)
				i++;
			else return ((unsigned char)(s1[i] + 32) - (unsigned char)s2[i]);
		}
		else if ('A' <= s2[i] && s2[i] <= 'Z')
		{
			if (s1[i] == s2[i] + 32)
				i++;
			else return ((unsigned char)s1[i] - (unsigned char)(s2[i] + 32));
		}
		else break;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void sort(char **array, int length)
{
	char *tmp;
	int min;

	for (int i = 0; i < length - 1; i++)
	{
		min = i;
		for (int j = i + 1; j < length; j++)
		{
			if (get_length(array[j]) < get_length(array[min]))
				min = j;
		}
		tmp = array[min];
		array[min] = array[i];
		array[i] = tmp;
	}
}

void sort_words(char **array, int total)
{
	int length;
	int start, end;
	char *tmp;
	int min;

	start = 0;
	end = 1;
	while (start < total)
	{
		length = get_length(array[start]);
		while (end < total && length == get_length(array[end]))
		{
			end++;
		}
		for (int i = start; i < end - 1; i++)
		{
			min = i;
			for (int j = i + 1; j < end; j++)
			{
				if (compare(array[j], array[min], length) < 0)
					min = j;
			}
			if (compare(array[min], array[i], length) < 0)
			{
				tmp = array[min];
				array[min] = array[i];
				array[i] = tmp;
			}
		}
		start = end;
	}
}

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		int length = get_word_amount(argv[1]);
		char **words = get_words(argv[1], length);
		sort(words, length);
		sort_words(words, length);
		int prev_length;
		for (int i = 0; words[i]; i++)
		{
			length = get_length(words[i]);
			if (i > 0)
			{
				if (prev_length == length)
					write(1, " ", 1);
				else write(1, "\n", 1);
			}
			write(1, words[i], length);
			prev_length = length;
		}
	}
	write(1, "\n", 1);
	return (0);
}
