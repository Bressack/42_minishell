/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_n.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 11:43:30 by frlindh           #+#    #+#             */
/*   Updated: 2019/12/09 11:33:45 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

void	to_n(int printed, int *dir, va_list ap)
{
	int	*ptr;

	if (dir[LONG] >= 0)
	{
		if (dir[LONG] == 0)
			ptr = (int *)va_arg(ap, long *);
		else
			ptr = (int *)va_arg(ap, long long *);
	}
	else if (dir[SHORT] >= 0)
	{
		if (dir[SHORT] == 0)
			ptr = (int *)va_arg(ap, short int *);
		else
			ptr = (int *)va_arg(ap, signed char *);
	}
	else
		ptr = va_arg(ap, int *);
	*ptr = printed;
}
