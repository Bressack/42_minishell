/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 09:48:27 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/17 14:30:57 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_strncpy(char *s1, const char *s2, size_t n)
{
	size_t	i1;
	size_t	i2;

	i1 = 0;
	i2 = 0;
	while (i2 < n && s2[i2] != '\0')
	{
		while (s2[i2] == '\\' || s2[i2] == '\'' || s2[i2] == '\"')
			i2++;
		s1[i1] = s2[i2];
		i1++;
		i2++;
	}
	while (i1 < n)
	{
		s1[i1] = '\0';
		i1++;
	}
	return (s1);
}

// char	*ft_strncpy(char *s1, const char *s2, size_t n)
// {
// 	size_t	i;
//
// 	i = 0;
// 	while (i < n && s2[i] != '\0')
// 	{
// 		s1[i] = s2[i];
// 		i++;
// 	}
// 	while (i < n)
// 	{
// 		s1[i] = '\0';
// 		i++;
// 	}
// 	return (s1);
// }
