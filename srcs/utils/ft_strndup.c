/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 18:51:21 by tharchen          #+#    #+#             */
/*   Updated: 2019/12/03 08:56:26 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ms.h>

static char		*ft_strncpy(char *s1, const char *s2, size_t n)
{
	size_t		i;

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

char			*ft_strndup(const char *src, size_t n)
{
	char		*dest;
	size_t		len;

	if (!src)
		return (NULL);
	len = ft_strlen(src) + 1;
	if (n > -1 && n < len)
		len = n + 1;
	dest = try_malloc(sizeof(char) * len, _FL_);
	ft_strncpy(dest, src, len);
	return (dest);
}
