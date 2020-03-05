/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 17:11:58 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/27 20:42:09 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// char	*ft_strdup(char *src)
// {
// 	char	*dest;
// 	size_t	len;
//
// 	if (!src)
// 		return (NULL);
// 	len = ft_strlen(src) + 1;
// 	if (!(dest = try_malloc(sizeof(char) * len, _FL_)))
// 		return (NULL);
// 	ft_strcpy(dest, src);
// 	return (dest);
// }

char	*ft_strdup(char *src)
{
	char	*dest;
	size_t	len;

	if (!src)
		return (NULL);
	len = ft_strlen(src) + 1;
	if (!(dest = mmalloc(sizeof(char) * len)))
		return (NULL);
	ft_strcpy(dest, src);
	return (dest);
}
