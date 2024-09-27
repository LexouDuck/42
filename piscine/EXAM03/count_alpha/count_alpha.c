/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_alpha.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 14:08:31 by exam              #+#    #+#             */
/*   Updated: 2017/09/22 14:39:44 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#define MAX 26

void add_letter(char *letters, int *count, char letter)
{
	for (int i = 0; i < MAX; i++)
	{
		if (letters[i] == letter)
		{
			count[i]++;
			return;
		}
	}
	for (int i = 0; i < MAX; i++)
	{
		if (count[i] == 0)
		{
			letters[i] = letter;
			count[i]++;
			return;
		}
	}
}

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		char *str = argv[1];
		char letters[MAX];
		int count[MAX];

		for (int i = 0; i < MAX; i++)
		{
			letters[i] = 0;
			count[i] = 0;
		}
		for (int i = 0; str[i]; i++)
		{
			if ('a' <= str[i] && str[i] <= 'z')
			{
				add_letter(letters, count, str[i]);
			}
			else if ('A' <= str[i] && str[i] <= 'Z')
			{
				add_letter(letters, count, str[i] - 'A' + 'a');
			}
		}
		for (int i = 0; i < MAX; i++)
		{
			if (letters[i])
			{
				printf("%d%c", count[i], letters[i]);
				if (letters[i + 1])
					printf(", ");
			}
			else break;
		}
	}
	printf("\n");
	return (0);
}
