/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 11:38:29 by frlindh           #+#    #+#             */
/*   Updated: 2020/03/07 16:22:14 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	in_charset(char *str, char *charset, int i)
{
	int		j;

	j = 0;
	while (charset[j])
	{
		if (str[i] == charset[j])
			return (1);
		j++;
	}
	return (0);
}

static char	*malloc_word(char *str, char *charset, int i)
{
	int		j;
	char	*word;

	j = i;
	while (str[j] && in_charset(str, charset, i) == 0)
		j++;
	if (!(word = (char *)mmalloc((j - i + 1) * sizeof(char))))
		return (NULL);
	return (word);
}

static char	**split_cpy(char *str, char *charset, char **split)
{
	int		i;
	int		j;
	int		c;

	i = 0;
	c = 0;
	while (str[i])
	{
		while (str[i] && in_charset(str, charset, i) == 1)
			i++;
		if (in_charset(str, charset, i) == 0)
		{
			split[c] = malloc_word(str, charset, i);
			j = -1;
			i = i - 1;
			while (str[++i] && in_charset(str, charset, i) == 0)
				split[c][++j] = str[i];
			split[c][j + 1] = '\0';
			c++;
		}
	}
	if (in_charset(str, charset, i - 1))
		c--;
	split[c] = NULL;
	return (split);
}

char		**ft_split(char *str, char *charset)
{
	char	**split;
	int		i;
	int		wc;

	i = 0;
	wc = 0;
	while (str[i])
	{
		while (str[i] && in_charset(str, charset, i) == 1)
			i++;
		if (in_charset(str, charset, i) == 0)
			wc++;
		while (str[i] && in_charset(str, charset, i) == 0)
			i++;
	}
	if (!(split = (char **)mmalloc((wc + 1) * sizeof(char *))))
		return (NULL);
	split_cpy(str, charset, split);
	return (split);
}
