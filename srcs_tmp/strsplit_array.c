/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsplit_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 19:06:52 by tharchen          #+#    #+#             */
/*   Updated: 2020/01/20 13:09:12 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_count_word(char const *s, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
			i++;
		if (s[i] != '\0' || s[i - 1] != c)
			j++;
	}
	return (j);
}

char		**ft_strsplit_array(char const *s, char *s)
{
	char	**str;
	int		i;
	int		j;
	int		l;

	j = 0;
	if (s == NULL)
		return (NULL);
	l = ft_count_word(s, c);
	str = try_malloc(sizeof(char *) * (l + 1), _FL_);
	i = 0;
	while (i < l)
	{
		j = 0;
		while (*s && *s == c)
			s = s + 1;
		while (*(s + j) && *(s + j) != c)
			j++;
		*(str++) = ft_substr(s, 0, j);
		s = s + j;
		i++;
	}
	*str = NULL;
	return (str - l);
}
