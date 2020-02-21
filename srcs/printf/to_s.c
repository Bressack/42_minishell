/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_s.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 12:06:13 by frlindh           #+#    #+#             */
/*   Updated: 2020/02/21 13:44:47 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>

int			to_s(char *buf, int *dir, va_list ap)
{
	char	*str;
	char	*s;
	char	fill;
	int		len;
	int		i;

	s = va_arg(ap, char *);
	s == NULL ? s = NULLSTR : 0;
	len = ft_strnlen(s, dir[PREC]);
	fill = ' ';
	if (dir[ZERO] == 1)
		fill = '0';
	str = buf;
	i = -1;
	if (dir[LEFT] != 1)
		while (len < dir[WIDTH]--)
			*str++ = fill;
	while (++i < len)
		*str++ = *s++;
	while (len < dir[WIDTH]--)
		*str++ = ' ';
	return (str - buf);
}
