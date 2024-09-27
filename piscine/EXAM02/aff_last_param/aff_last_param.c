/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_last_param.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 18:09:51 by exam              #+#    #+#             */
/*   Updated: 2017/09/15 18:20:35 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int main(int argc, char **argv)
{
	const int last = argc - 1;
	char c;
	int i = 0;
	if (last)
	{
		while (argv[last][i])
		{
			c = argv[last][i];
			write(1, &c, 1);
			i++;
		}
	}
	c = '\n';
	write(1, &c, 1);
}
