/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 21:17:14 by aduquesn          #+#    #+#             */
/*   Updated: 2017/09/12 13:53:33 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	*recursive_power(int n, int *nb, int *result);

int	ft_recursive_power(int nb, int power)
{
	int result;
	int i;

	result = 1;
	i = 0;
	if (power < 0)
		return (0);
	else if (power == 0)
		return (1);
	else if (nb == 0)
		return (0);
	else if (nb == 1)
		return (1);
	else
	{
		recursive_power(power, &nb, &result);
	}
	return (result);
}

int	*recursive_power(int n, int *nb, int *result)
{
	if (n > 0)
	{
		*result *= *nb;
		return (recursive_power(n - 1, nb, result));
	}
	else
		return (result);
}
