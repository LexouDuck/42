/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 18:21:23 by exam              #+#    #+#             */
/*   Updated: 2017/09/08 19:17:13 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int num1;
	char operator;
	int num2;
	int result;
	
	if (argc != 4)
	{
		printf("\n");
		return 1;
	}
	num1 = atoi(argv[1]);
	operator = argv[2][0];
	num2 = atoi(argv[3]);
	result = 0;
	switch (operator)
	{
		case '+': result = num1 + num2; break;
		case '-': result = num1 - num2; break;
		case '*': result = num1 * num2; break;
		case '/': result = num1 / num2; break;
		case '%': result = num1 % num2; break;
	}
	printf("%d\n", result);
	return 0;
}
