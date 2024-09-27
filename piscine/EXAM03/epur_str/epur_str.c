/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epur_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 11:45:08 by exam              #+#    #+#             */
/*   Updated: 2017/09/22 12:35:37 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		char *str = argv[1];
		int flag = 0;
		int i = 0;

		while  (str[i] == ' ' ||
				str[i] == '	' ||
				str[i] == '\n')
		{
			i++;
		}
		while (str[i])
		{
			while  (str[i] == ' ' ||
					str[i] == '	' ||
					str[i] == '\n')
			{
				flag = 1;
				i++;
			}
			if (str[i])
			{
				if (flag)
				{
					write(1, " ", 1);
					flag = 0;
				}
				write(1, str + i, 1);
				i++;
			}
		}
	}
	write(1, "\n", 1);
	return (0);
}
