/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hidenp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 19:45:53 by exam              #+#    #+#             */
/*   Updated: 2017/09/08 19:58:00 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int main(int argc, char **argv)
{
	char *query = argv[1];
	char *str = argv[2];
	char c;
	int i;
	int j;
	
	if (argc != 3)
	{
		c = '\n';
		write(1, &c, 1);
		return 1;
	}
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == query[j])
		{
			query[j] = 127;
			j++;
		}
		i++;
	}
	i = 0;
	while (query[i])
	{
		if (query[i] == 127) c = '1';
		else
		{
			c = '0';
			break;
		}
		i++;
	}
	write(1, &c, 1);
	c = '\n';
	write(1, &c, 1);
	return 0;
}
