/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 16:37:35 by aduquesn          #+#    #+#             */
/*   Updated: 2017/11/30 19:20:24 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_putchar(char c);

int		compare(char *s1, char *s2)
{
	unsigned int	i;

	if (s1 == s2)
		return (0);
	if (s1 && s2)
	{
		i = 0;
		while (s1[i] && s2[i])
		{
			if (s1[i] != s2[i])
			{
				return (s1[i] - s2[i]);
			}
			i++;
		}
		return (s1[i] - s2[i]);
	}
	return ((s1 ? s1[0] : 0) -
			(s2 ? s2[0] : 0));
}

void	sort(char **args, int size)
{
	char	*ptr;
	int		min;
	int		i;
	int		j;

	i = 0;
	while (i < size)
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

void	copy(char **dest, char **src, int n)
{
	int i;

	i = 1;
	while (i < n)
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

	copy(args, argv, argc);
	sort(args, argc - 1);
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
