/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ulstr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 10:49:33 by exam              #+#    #+#             */
/*   Updated: 2017/09/22 11:00:07 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		char *str = argv[1];
		int i = 0;

		while (str[i])
		{
			if ('a' <= str[i] && str[i] <= 'z')
			{
				str[i] -= 'a';
				str[i] += 'A';
			}
			else if ('A' <= str[i] && str[i] <= 'Z')
			{
				str[i] -= 'A';
				str[i] += 'a';
			}
			i++;
		}
		write(1, str, i);
	}
	write(1, "\n", 1);
	return (0);
}
