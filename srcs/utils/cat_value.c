/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 21:35:45 by frlindh           #+#    #+#             */
/*   Updated: 2020/02/27 20:35:20 by frlindh          ###   ########.fr       */
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
	if (!(s1 = (char *)mmalloc(i + j + 1)))
		return (NULL);
	j = -1;
	while (s2 && s2[++j])
		s1[i + j] = s2[j];
	s1[i + j] = '\0';
	return (s1);
}

/*
** char	*cat_value(char *s1, char **s2)
** {
** 	int		i;
** 	int		j;
**
** 	i = 0;
** 	while (s1 && s1[i])
** 		i++;
** 	j = 0;
** 	while (s2 && s2[0][j] && s2[0][j] != ' ')
** 		j++;
** 	if (!(s1 = (char *)realloc(s1, i + j)))
** 		return (NULL);
** 	while (s2 && **s2 && **s2 != ' ')
** 	{
** 		s1[i] = *((*s2)++);
** 		i++;
** 	}
** 	s1[i] = '\0';
** 	return (s1);
** }
*/
