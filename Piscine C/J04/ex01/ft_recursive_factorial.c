/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 17:12:21 by aduquesn          #+#    #+#             */
/*   Updated: 2017/09/12 13:52:15 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	*recursive_factorial(int n, int *result);

int	ft_recursive_factorial(int nb)
{
	int result;

	result = 1;
	if (nb == 0 || nb == 1)
		return (1);
	else if (nb < 0 || nb > 12)
		return (0);
	else
		return (*recursive_factorial(nb, &result));
}

int	*recursive_factorial(int n, int *result)
{
	if (n > 0)
	{
		*result *= n;
		return (recursive_factorial(n - 1, result));
	}
	else
		return (result);
}
