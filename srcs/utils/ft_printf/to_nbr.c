/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_nbr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 12:05:29 by frlindh           #+#    #+#             */
/*   Updated: 2020/03/07 16:21:53 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static void			ft_itoa_b(char *addr, unsigned long long nbr, int *dir)
{
	char			*xbase;
	int				i;
	char			n[70];
	int				base;

	i = 0;
	base =
	(dir[PF_SPEC] == 6 || dir[PF_SPEC] == 7 || dir[PF_SPEC] == 2) ? 16 : 10;
	xbase = (dir[PF_SPEC] == 7) ? "0123456789ABCDEF" : "0123456789abcdef";
	if (nbr == 0 && dir[PF_PREC] != 0)
		n[i++] = '0';
	while (nbr != 0)
	{
		n[i++] = xbase[nbr % base];
		nbr = nbr / base;
	}
	n[i] = '\0';
	while (addr && --i >= 0)
		*addr++ = n[i];
	*addr = '\0';
}

static char			*ft_number_str(char *n, char *str, char sign, int *dir)
{
	int				len;

	len = ft_strnlen(n, -1);
	if (dir[PF_LEFT] != 1 && dir[PF_ZERO] != 1)
		while (0 < dir[PF_WIDTH]--)
			*str++ = ' ';
	if (sign != 0)
		*str++ = sign;
	if (dir[PF_SPEC] == 2 || (dir[PF_S] == 1 && dir[PF_SPEC] >= 6 &&
		dir[PF_SPEC] <= 7))
	{
		*str++ = '0';
		*str++ = (dir[PF_SPEC] == 7) ? 'X' : 'x';
	}
	if (dir[PF_LEFT] != 1)
		while (0 < dir[PF_WIDTH]--)
			*str++ = '0';
	while (dir[PF_PREC]-- > len)
		*str++ = '0';
	while (n && *n && len-- > 0)
		*str++ = *n++;
	while (0 < dir[PF_WIDTH]--)
		*str++ = ' ';
	return (str);
}

static long long	get_nbr(int *dir, va_list ap)
{
	if (dir[PF_SPEC] == 2)
		return ((unsigned long long)va_arg(ap, void *));
	else if (dir[PF_SPEC] == 5 || dir[PF_SPEC] == 6 || dir[PF_SPEC] == 7)
	{
		if (dir[PF_LONG] == 0)
			return ((unsigned long long)va_arg(ap, unsigned long));
		else if (dir[PF_LONG] == 1)
			return (va_arg(ap, unsigned long long));
		else if (dir[PF_SHORT] == 0)
			return ((unsigned short int)va_arg(ap, unsigned int));
		else if (dir[PF_SHORT] == 1)
			return ((unsigned char)va_arg(ap, unsigned int));
		else
			return ((unsigned long long)va_arg(ap, unsigned int));
	}
	if (dir[PF_LONG] == 0)
		return ((long long)va_arg(ap, long));
	else if (dir[PF_LONG] == 1)
		return ((long long)va_arg(ap, long long));
	else if (dir[PF_SHORT] == 0)
		return ((short int)va_arg(ap, int));
	else if (dir[PF_SHORT] == 1)
		return ((signed char)va_arg(ap, int));
	else
		return ((long long)va_arg(ap, int));
}

int					to_nbr(char *buf, int *dir, va_list ap)
{
	long long		nbr;
	char			sign;
	char			n[70];

	if (!(sign = 0) && (dir[PF_SPEC] == 3 || dir[PF_SPEC] == 4))
	{
		nbr = get_nbr(dir, ap);
		sign = (dir[PF_SPACE] == 1) ? ' ' : 0;
		sign = (dir[PF_PLUS] == 1) ? '+' : sign;
		sign = (nbr < 0) ? '-' : sign;
		dir[PF_WIDTH] = (sign != 0) ? dir[PF_WIDTH] - 1 : dir[PF_WIDTH];
	}
	if ((dir[PF_SPEC] == 3 || dir[PF_SPEC] == 4) && nbr >= 0)
		ft_itoa_b(n, (unsigned long long)nbr, dir);
	else if (dir[PF_SPEC] == 3 || dir[PF_SPEC] == 4)
		ft_itoa_b(n, (unsigned long long)-nbr, dir);
	else
		ft_itoa_b(n, (unsigned long long)get_nbr(dir, ap), dir);
	dir[PF_PREC] != -1 ? dir[PF_ZERO] = -1 : 0;
	dir[PF_PREC] = dir[PF_PREC] < ft_strnlen(n, -1) ?
	ft_strnlen(n, -1) : dir[PF_PREC];
	dir[PF_WIDTH] = dir[PF_WIDTH] - dir[PF_PREC];
	n[0] == '\0' || n[0] == '0' ? dir[PF_S] = -1 : 0;
	(dir[PF_SPEC] == 2 || dir[PF_S] == 1) ? dir[PF_WIDTH] -= 2 : 0;
	return (ft_number_str(n, buf, sign, dir) - buf);
}
