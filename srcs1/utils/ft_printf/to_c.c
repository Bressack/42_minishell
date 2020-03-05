/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_c.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 12:06:37 by frlindh           #+#    #+#             */
/*   Updated: 2020/03/04 12:26:46 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int			to_c(char *buf, int *dir, va_list ap)
{
	char	*str;
	char	fill;

	str = buf;
	fill = ' ';
	dir[PF_WIDTH]--;
	if (dir[PF_PREC] == -1 && dir[PF_ZERO] == 1)
		fill = '0';
	if (dir[PF_LEFT] != 1)
		while (0 < dir[PF_WIDTH]--)
			*str++ = fill;
	if (dir[PF_SPEC] == -1)
		*str++ = '\0';
	else
		*str++ = (dir[PF_SPEC] == 8) ? '%' : va_arg(ap, int);
	while (0 < dir[PF_WIDTH]--)
		*str++ = ' ';
	return (dir[PF_SPEC] == -1) ? (str - buf - 1) : (str - buf);
}
