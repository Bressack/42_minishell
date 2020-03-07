/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 21:35:45 by frlindh           #+#    #+#             */
/*   Updated: 2020/03/07 18:48:23 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*cat_value(char *s1, char c, char *s2)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	while (s1 && s1[i])
		i++;
	j = 0;
	while (s2 && s2[j])
		j++;
	if (!(ret = (char *)mmalloc(i + j + 2)))
		return (NULL);
	i = -1;
	while (s1 && s1[++i])
		ret[i] = s1[i];
	mfree((void **)&s1);
	(c) ? ret[i++] = c : 0;
	j = -1;
	while (s2 && s2[++j])
		ret[i + j] = s2[j];
	ret[i + j] = '\0';
	return (ret);
}
