/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 12:17:15 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/07 08:01:11 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t		length;
	char		*out;

	if (s == NULL)
		return (NULL);
	length = ft_strlen(s);
	out = NULL;
	if ((start + len) <= length)
	{
		out = mmalloc(sizeof(char) * (len + 1));
		if (out)
		{
			out = ft_strncpy(out, s + start, len);
			out[len] = '\0';
		}
	}
	return (out);
}
