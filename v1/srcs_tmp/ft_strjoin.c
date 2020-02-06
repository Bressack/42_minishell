/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 01:31:08 by tharchen          #+#    #+#             */
/*   Updated: 2019/11/30 18:01:59 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ms.h>

static void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (i < n)
	{
		str1[i] = str2[i];
		i++;
	}
	return (str1);
}

static void	*join(char **ret, char *arg, int *retsize)
{
	char	*tmp;
	int		size;

	size = ft_strlen(arg);
	tmp = try_malloc(sizeof(char) * (*retsize + size + 1), _FL_);
	ft_memcpy(tmp, *ret, *retsize);
	ft_memcpy(tmp + *retsize, arg, size);
	*retsize += size;
	tmp[*retsize] = '\0';
	try_free_((void **)ret, _FL_);
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
			ret = ft_strndup(arg, -1);
			size = ft_strlen(ret);
		}
		else
			join(&ret, arg, &size);
	}
	va_end(ap);
	return (ret);
}
