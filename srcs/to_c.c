/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_c.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 12:06:37 by frlindh           #+#    #+#             */
/*   Updated: 2020/02/21 13:44:27 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>

int			to_c(char *buf, int *dir, va_list ap)
{
	char	*str;
	char	fill;

	str = buf;
	fill = ' ';
	dir[WIDTH]--;
	if (dir[PREC] == -1 && dir[ZERO] == 1)
		fill = '0';
	if (dir[LEFT] != 1)
		while (0 < dir[WIDTH]--)
			*str++ = fill;
	if (dir[SPEC] == -1)
		*str++ = '\0';
	else
		*str++ = (dir[SPEC] == 8) ? '%' : va_arg(ap, int);
	while (0 < dir[WIDTH]--)
		*str++ = ' ';
	return (dir[SPEC] == -1) ? (str - buf - 1) : (str - buf);
}
