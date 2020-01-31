/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 18:51:21 by tharchen          #+#    #+#             */
/*   Updated: 2020/01/31 02:04:51 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ms.h>

static char		*ft_strncpy(char *s1, const char *s2, long n)
{
	long		i;

	i = 0;
	while (i < n && s2[i] != '\0')
	{
		s1[i] = s2[i];
		i++;
	}
	while (i < n)
	{
		s1[i] = '\0';
		i++;
	}
	return (s1);
}

char			*ft_strndup(const char *src, long n)
{
	char		*dest;
	long		len;

	if (!src)
		return (NULL);
	len = ft_strlen(src);
	if (n > -1 && n < len)
		len = n;
	dest = try_malloc(sizeof(char) * (len + 1), _FL_);
	ft_strncpy(dest, src, len);
	return (dest);
}
