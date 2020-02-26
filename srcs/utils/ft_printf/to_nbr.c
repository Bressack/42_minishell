/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_nbr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 12:05:29 by frlindh           #+#    #+#             */
/*   Updated: 2020/02/26 04:28:22 by tharchen         ###   ########.fr       */
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
	base = (dir[PRINTF_SPEC] == 6 || dir[PRINTF_SPEC] == 7 || dir[PRINTF_SPEC] == 2) ? 16 : 10;
	xbase = (dir[PRINTF_SPEC] == 7) ? "0123456789ABCDEF" : "0123456789abcdef";
	if (nbr == 0 && dir[PRINTF_PREC] != 0)
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
	if (dir[PRINTF_LEFT] != 1 && dir[PRINTF_ZERO] != 1)
		while (0 < dir[PRINTF_WIDTH]--)
			*str++ = ' ';
	if (sign != 0)
		*str++ = sign;
	if (dir[PRINTF_SPEC] == 2 || (dir[PRINTF_S] == 1 && dir[PRINTF_SPEC] >= 6 && dir[PRINTF_SPEC] <= 7))
	{
		*str++ = '0';
		*str++ = (dir[PRINTF_SPEC] == 7) ? 'X' : 'x';
	}
	if (dir[PRINTF_LEFT] != 1)
		while (0 < dir[PRINTF_WIDTH]--)
			*str++ = '0';
	while (dir[PRINTF_PREC]-- > len)
		*str++ = '0';
	while (n && *n && len-- > 0)
		*str++ = *n++;
	while (0 < dir[PRINTF_WIDTH]--)
		*str++ = ' ';
	return (str);
}

static long long	get_nbr(int *dir, va_list ap)
{
	if (dir[PRINTF_SPEC] == 2)
		return ((unsigned long long)va_arg(ap, void *));
	else if (dir[PRINTF_SPEC] == 5 || dir[PRINTF_SPEC] == 6 || dir[PRINTF_SPEC] == 7)
	{
		if (dir[PRINTF_LONG] == 0)
			return ((unsigned long long)va_arg(ap, unsigned long));
		else if (dir[PRINTF_LONG] == 1)
			return (va_arg(ap, unsigned long long));
		else if (dir[PRINTF_SHORT] == 0)
			return ((unsigned short int)va_arg(ap, unsigned int));
		else if (dir[PRINTF_SHORT] == 1)
			return ((unsigned char)va_arg(ap, unsigned int));
		else
			return ((unsigned long long)va_arg(ap, unsigned int));
	}
	if (dir[PRINTF_LONG] == 0)
		return ((long long)va_arg(ap, long));
	else if (dir[PRINTF_LONG] == 1)
		return ((long long)va_arg(ap, long long));
	else if (dir[PRINTF_SHORT] == 0)
		return ((short int)va_arg(ap, int));
	else if (dir[PRINTF_SHORT] == 1)
		return ((signed char)va_arg(ap, int));
	else
		return ((long long)va_arg(ap, int));
}

int					to_nbr(char *buf, int *dir, va_list ap)
{
	long long		nbr;
	char			sign;
	char			n[70];

	sign = 0;
	if (dir[PRINTF_SPEC] == 3 || dir[PRINTF_SPEC] == 4)
	{
		nbr = get_nbr(dir, ap);
		sign = (dir[PRINTF_SPACE] == 1) ? ' ' : 0;
		sign = (dir[PRINTF_PLUS] == 1) ? '+' : sign;
		sign = (nbr < 0) ? '-' : sign;
		dir[PRINTF_WIDTH] = (sign != 0) ? dir[PRINTF_WIDTH] - 1 : dir[PRINTF_WIDTH];
	}
	if ((dir[PRINTF_SPEC] == 3 || dir[PRINTF_SPEC] == 4) && nbr >= 0)
		ft_itoa_b(n, (unsigned long long)nbr, dir);
	else if (dir[PRINTF_SPEC] == 3 || dir[PRINTF_SPEC] == 4)
		ft_itoa_b(n, (unsigned long long)-nbr, dir);
	else
		ft_itoa_b(n, (unsigned long long)get_nbr(dir, ap), dir);
	dir[PRINTF_PREC] != -1 ? dir[PRINTF_ZERO] = -1 : 0;
	dir[PRINTF_PREC] = dir[PRINTF_PREC] < ft_strnlen(n, -1) ? ft_strnlen(n, -1) : dir[PRINTF_PREC];
	dir[PRINTF_WIDTH] = dir[PRINTF_WIDTH] - dir[PRINTF_PREC];
	n[0] == '\0' || n[0] == '0' ? dir[PRINTF_S] = -1 : 0;
	(dir[PRINTF_SPEC] == 2 || dir[PRINTF_S] == 1) ? dir[PRINTF_WIDTH] = dir[PRINTF_WIDTH] - 2 : 0;
	return (ft_number_str(n, buf, sign, dir) - buf);
}
