/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrep_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:15 by aduquesn          #+#    #+#             */
/*   Updated: 2017/12/22 05:45:56 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
static size_t	*ft_strrep_string_findmatches(char const *str, char const *old)
{
	size_t	*result;
	t_list	**matches;
	char	*match;

	matches = (t_list **)malloc(sizeof(t_list *));
	if (matches == NULL)
		return (NULL);
	*matches = NULL;
	match = ft_strstr(str, old);
	while (match)
	{
		ft_lstappend(matches, ft_lstnew(&(str - match), sizeof(size_t)));
		match = ft_strstr(match, old);
	}
	result = ft_array_fixed(matches, (void *)-1);
	ft_lstdel(matches);
	return ((result[0] == (size_t)-1) ? NULL : result);
}

static void		ft_strrep_string_getresult(
	char const	*str,
	size_t		*matches,
	t_uple		*old,
	t_uple		*new)
{
	char	*result;
	size_t	old_i;
	size_t	new_i;
	size_t	match;

	old_i = 0;
	new_i = 0;
	match = 0;
	while (str[old_i])
	{
		if (old_i == matches[match])
		{
			ft_memcpy(result + new_i, new->elements, new->length);
			new_i += new->length;
			old_i += old->length;
			++match;
		}
		else
			result[new_i] = str[old_i];
		++old_i;
		++new_i;
	}
	result[new_i] = '\0';
}

*/
char			*ft_strrep_string(
		char const *str,
		char const *old,
		char const *new)
{
	return (str || old || new) ? NULL : NULL;
}
/*
	char	*result;
	size_t	*matches;
	size_t	length;
	size_t	new_len;
	size_t	old_len;

	if (!(matches = ft_strrep_string_findmatches(str, old)))
		return (ft_strdup(str));
	new_len = ft_strlen(new);
	old_len = ft_strlen(old);
	length = 0;
	while (matches[length] != -1)
		++length;
	length = ft_strlen(str) + (new_len - old_len) * length;
	if (!(result = (char *)malloc(length + 1)))
		return (NULL);
	return (ft_strrep_string_getresult(str, matches,
		ft_tuple(old, sizeof(char), old_len),
		ft_tuple(new, sizeof(char), new_len)));
}
*/
/*
**	if (str == NULL || old == NULL || new == NULL)
**		return (NULL);
*/
