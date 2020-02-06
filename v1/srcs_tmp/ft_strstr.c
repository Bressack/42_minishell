/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:58:05 by tharchen          #+#    #+#             */
/*   Updated: 2020/01/09 15:03:55 by ssingevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ms.h>

int			ft_strfind(char *s, int c)
{
	int		i;

	i = -1;
	while (s[++i])
		if (s[i] == c)
			return (i);
	return (-1);
}

int			ft_strstr(const char *haystack, const char *needle)
{
	int i;
	int pos;
	int len;

	i = 0;
	pos = 0;
	len = 0;
	while (needle[len] != '\0')
		len++;
	if (len == 0)
		return (0);
	while (haystack[i])
	{
		while (needle[pos] == haystack[i + pos])
		{
			if (pos == len - 1)
				return (i);
			pos++;
		}
		pos = 0;
		i++;
	}
	return (-1);
}
