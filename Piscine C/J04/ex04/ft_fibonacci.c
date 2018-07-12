/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fibonacci.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 12:12:20 by aduquesn          #+#    #+#             */
/*   Updated: 2017/09/12 13:53:43 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	*recursive_fibonacci(int n, int prev, int *index, int *result);

int	ft_fibonacci(int index)
{
	int result;

	result = 1;
	if (index < 0)
		return (-1);
	else if (index == 0)
		return (0);
	else
		return (*recursive_fibonacci(1, 0, &result, &index));
}

int	*recursive_fibonacci(int n, int prev, int *result, int *index)
{
	int temp;

	if (n < *index)
	{
		temp = *result;
		*result += prev;
		recursive_fibonacci(n + 1, temp, result, index);
	}
	return (result);
}
