/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_n.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 11:43:30 by frlindh           #+#    #+#             */
/*   Updated: 2020/02/21 13:44:26 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

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
