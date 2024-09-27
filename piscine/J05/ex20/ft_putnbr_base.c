/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 18:52:35 by aduquesn          #+#    #+#             */
/*   Updated: 2017/09/12 20:31:52 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_putchar(char c);

int		check_base(int nbr, char *base)
{
	int i;
	int j;

	if (nbr == 0)
	{
		ft_putchar(base[0]);
		return (0);
	}
	i = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		j = i - 1;
		while (j >= 0)
		{
			if (base[i] == base[j])
				return (0);
			j--;
		}
		i++;
	}
	return ((i == 1) ? 0 : i);
}

void	ft_putnbr_base(int nbr, char *base)
{
	char	digits[10];
	int		length;
	long	n;
	int		i;

	length = check_base(nbr, base);
	if (length == 0)
		return ;
	else if (nbr < 0)
	{
		n = (long)nbr * -1;
		ft_putchar('-');
	}
	else
		n = nbr;
	i = 0;
	while (n > 0)
	{
		digits[i++] = base[n % length];
		n /= length;
	}
	while (i--)
		ft_putchar(digits[i]);
}
