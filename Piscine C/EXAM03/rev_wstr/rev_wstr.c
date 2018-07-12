/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_wstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 12:35:26 by exam              #+#    #+#             */
/*   Updated: 2017/09/22 13:20:42 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

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

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		char **words;
		char *str = argv[1];
		int n;
		int i;

		n = get_word_amount(str) + 1;
		words = malloc(n * sizeof(char*));
		if (words == NULL) return (1);
		words[--n] = NULL;
		n = 0;
		i = 0;
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
				words[n++] = str + i;
				while  (str[i] &&
						str[i] != ' ' &&
						str[i] != '	' &&
						str[i] != '\n')
				{
					i++;
				}
			}
		}
		while (n--)
		{
			i = 0;
			while  (words[n][i] &&
					words[n][i] != ' ' &&
					words[n][i] != '	' &&
					words[n][i] != '\n')
			{
				write(1, words[n] + i, 1);
				i++;
			}
			if (n > 0)
			{
				write(1, " ", 1);
			}
		}
	}
	write(1, "\n", 1);
	return (0);
}
