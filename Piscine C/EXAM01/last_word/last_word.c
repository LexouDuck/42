/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 18:21:23 by exam              #+#    #+#             */
/*   Updated: 2017/09/08 18:59:27 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int main(int argc, char **argv)
{
	char c = '\n';
	char *str = argv[1];
	int flag = 0;
	int i = 0;
	
	if (argc != 2)
	{
		write(1, &c, 1);
		return 1;
	}
	while (str[i]) i++;
	while (i--)
	{
		if (str[i] == 32 || str[i] == 9)
		{
			if (flag)
			{
				i += 1;
				break;
			}
		}
		else flag = 1;
	}
	while (str[i])
	{	
		if (str[i] == 32 || str[i] == 9) break;
		write(1, &str[i], 1);
		i++;
	}
	write(1, &c, 1);
	return 0;
}
