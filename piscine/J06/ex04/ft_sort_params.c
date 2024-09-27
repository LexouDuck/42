/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 16:37:35 by aduquesn          #+#    #+#             */
/*   Updated: 2017/09/13 20:24:12 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putchar(char c);

int		compare(char *s1, char *s2)
{
	unsigned char	c1;
	unsigned char	c2;
	unsigned int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
		{
			c1 = s1[i];
			c2 = s2[i];
			return (c1 - c2);
		}
		i++;
	}
	return (0);
}

void	sort(char **args, int size)
{
	char	*ptr;
	int		min;
	int		i;
	int		j;

	i = 0;
	while (i < size - 1)
	{
		min = i;
		j = i + 1;
		while (j < size)
		{
			if (compare(args[j], args[min]) < 0)
				min = j;
			j++;
		}
		if (min != i)
		{
			ptr = args[i];
			args[i] = args[min];
			args[min] = ptr;
		}
		i++;
	}
}

void	copy(char **dest, char **src)
{
	int i;

	i = 1;
	while (src[i])
	{
		dest[i - 1] = src[i];
		i++;
	}
}

int		main(int argc, char **argv)
{
	char	*args[argc - 1];
	int		i;
	int		j;

	copy(args, argv);
	sort(args, argc);
	i = 0;
	while (i < argc - 1)
	{
		j = 0;
		while (args[i][j])
		{
			ft_putchar(args[i][j]);
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}
