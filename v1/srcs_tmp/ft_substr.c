/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 12:17:15 by tharchen          #+#    #+#             */
/*   Updated: 2020/01/19 17:26:27 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ms.h>

char			*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*new_s;
	int			i;

	if (!s)
		return (NULL);
	if (ft_strlen(s) == 0)
		return ("");
	new_s = try_malloc(sizeof(char) * (len + 1), _FL_);
	i = 0;
	while (s[start] && i < (int)len)
	{
		new_s[i] = s[start];
		start++;
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}
