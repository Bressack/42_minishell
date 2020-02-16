/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:57:22 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/16 12:17:53 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0 && *s1 && *s2 && (*s1 == *s2))
	{
		n--;
		s1++;
		s2++;
	}
	return (n ? (*(unsigned char *)s1) - (*(unsigned char *)s2) : 0);
}
