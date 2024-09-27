/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 18:41:53 by exam              #+#    #+#             */
/*   Updated: 2017/09/15 19:04:50 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void print(int *chars, char *arg);

int main(int argc, char **argv)
{
	int chars[256];
	char c;

	if (argc == 3)
	{
		for (int i = 0; i < 256; i++)
		{
			chars[i] = 1;
		}
		print(chars, argv[1]);
		print(chars, argv[2]);
	}
	c = '\n';
	write(1, &c, 1);
	return (0);
}

void print(int *chars, char *arg)
{
	int i = 0;
	int c;
	while (arg[i])
	{
		c = arg[i];
		if (chars[c])
		{
			write(1, &c, 1);
			chars[c] = 0;
		}
		i++;
	}
}
