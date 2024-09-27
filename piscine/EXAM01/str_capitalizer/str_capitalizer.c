/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_capitalizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 19:22:26 by exam              #+#    #+#             */
/*   Updated: 2017/09/08 19:39:51 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#define UPPERCASE 0
#define LOWERCASE 1

void capitalize(char *str);

int main(int argc, char **argv)
{
	char c = '\n';
	int i;
	
	if (argc == 1)
	{
		write(1, &c, 1);
		return 1;
	}
	i = 1;
	while (i < argc)
	{	
		capitalize(argv[i]);
		i++;
	}
	return 0;
}

void capitalize(char *str)
{
	int state = UPPERCASE;
	char c = 0;
	int i = 0;

	while (str[i])
	{
		if ('a' <= str[i] && str[i] <= 'z')
		{
			if (state == LOWERCASE)
				 c = str[i];
			else c = str[i] - 'a' + 'A';
			state = LOWERCASE;
		}
		else if ('A' <= str[i] && str[i] <= 'Z')
		{
			if (state == UPPERCASE)
				 c = str[i];
			else c = str[i] - 'A' + 'a';
			state = LOWERCASE;
		}
		else c = str[i];

		if (str[i] == ' ' || str[i] == '\t')
		{
			state = UPPERCASE;
		}
		write(1, &c, 1);
		i++;
	}
	c = '\n';
	write(1, &c, 1);
}
