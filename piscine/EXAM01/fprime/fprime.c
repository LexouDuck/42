/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fprime.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 20:03:29 by exam              #+#    #+#             */
/*   Updated: 2017/09/08 20:29:16 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int is_prime(int n);

int main(int argc, char **argv)
{
	int i;
	int n;

	if (argc != 2)
	{
		printf("\n");
		return 1;
	}
	else n = atoi(argv[1]);
	i = 2;
	if (n < i)
	{
		printf("%d\n", n);
		return 0;
	}
	while (i < n)
	{
		if (n % i == 0 && is_prime(i))
		{
			n /= i;
			printf("%d", i);
			if (n == 0) break;
			else printf("*");
			continue;
		}
		i++;
	}
	printf("%d\n", i);
	return 0;
}

int is_prime(int n)
{
	int i = 2;
	while (i * 2 < n)
	{
		if (n % i == 0)
			return 0;
		i++;
	}
	return 1;
}
