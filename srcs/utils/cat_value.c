/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 21:35:45 by frlindh           #+#    #+#             */
/*   Updated: 2020/03/03 16:05:49 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*cat_value(char *s1, char *s2)
{
	int		i;
	int		j;

	i = 0;
	while (s1 && s1[i])
		i++;
	j = 0;
	while (s2 && s2[j])
		j++;
	if (!(s1 = (char *)mrealloc(s1, i + j + 1)))
		return (NULL);
	j = -1;
	while (s2 && s2[++j])
		s1[i + j] = s2[j];
	s1[i + j] = '\0';
	return (s1);
}
