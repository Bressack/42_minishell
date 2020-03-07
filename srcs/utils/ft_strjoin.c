/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 01:31:08 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/07 16:19:04 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	*join(char **ret, char *arg, int *retsize)
{
	char	*tmp;
	int		size;

	size = ft_strlen(arg);
	tmp = mmalloc(sizeof(char) * (*retsize + size + 1));
	ft_memcpy(tmp, *ret, *retsize);
	ft_memcpy(tmp + *retsize, arg, size);
	*retsize += size;
	tmp[*retsize] = '\0';
	mfree((void **)ret);
	*ret = tmp;
	return (tmp);
}

char		*ft_strjoin(int nb_str, ...)
{
	char	*arg;
	char	*ret;
	va_list	ap;
	int		size;

	ret = NULL;
	size = 0;
	va_start(ap, nb_str);
	while (nb_str--)
	{
		if (!(arg = va_arg(ap, char *)))
			continue ;
		if (!ret)
		{
			if (!(ret = ft_strdup(arg)))
				return (NULL);
			size = ft_strlen(ret);
		}
		else if (join(&ret, arg, &size) == NULL)
			return (NULL);
	}
	va_end(ap);
	return (ret);
}
