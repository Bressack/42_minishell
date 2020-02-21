/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 10:37:08 by frlindh           #+#    #+#             */
/*   Updated: 2020/02/17 13:45:44 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

static int	ft_iscspec(const char c)
{
	int		i;

	i = -1;
	while (C_SPEC[++i])
		if (C_SPEC[i] == c)
			return (i);
	return (-1);
}

static void	ft_specifier(int *dir, const char **format, int i, va_list ap)
{
	while (**format == 'h' || **format == 'l')
	{
		if (**format == 'l')
			dir[LONG]++;
		if (**format == 'h')
			dir[SHORT]++;
		(*format)++;
	}
	(dir[SPEC] = ft_iscspec(**format)) >= 0 ? (*format)++ : 0;
	if (dir[SPEC] == 9)
		to_n(i, dir, ap);
}

static void	ft_initdir(int *dir, const char **f, va_list ap)
{
	while (**f == '+' || **f == '-' || **f == '.' || **f == '#' || **f == ' ' ||
	**f == '\'' || (**f >= '0' && **f <= '9'))
	{
		dir[ZERO] = (**f == '0') ? 1 : dir[ZERO];
		dir[LEFT] = (**f == '-') ? 1 : dir[LEFT];
		dir[PLUS] = (**f == '+') ? 1 : dir[PLUS];
		dir[SPACE] = (**f == ' ') ? 1 : dir[SPACE];
		dir[S] = (**f == '#') ? 1 : dir[S];
		if (**f == '.' && (*f)++ && (dir[PREC] = 0) == 0)
		{
			if (**f >= '0' && **f <= '9')
				dir[PREC] = skip_atoi(f);
			else if (**f == '*' && (*f)++ && (dir[PREC] = va_arg(ap, int)) < 0)
				dir[PREC] = -dir[PREC];
		}
		else if (**f >= '1' && **f <= '9')
			dir[WIDTH] = skip_atoi(f);
		else if (**f == '*' && (*f)++ && (dir[WIDTH] = va_arg(ap, int)) < 0)
		{
			dir[LEFT] = 1;
			dir[WIDTH] = -dir[WIDTH];
		}
		else
			(*f)++;
	}
}

static int	ft_cont(char *buf, const char **format, va_list ap, int i)
{
	int		dir[11];
	int		j;

	while (**format && i < BUFF_SIZE - 65)
	{
		if ((j = 11) == 11 && **format != '%')
			buf[i++] = *(*format)++;
		else
		{
			(*format)++;
			while (j > 0)
				dir[--j] = -1;
			ft_initdir(dir, format, ap);
			ft_specifier(dir, format, i, ap);
			if (dir[SPEC] < 1 || dir[SPEC] == 8)
				i += to_c(&buf[i], dir, ap);
			else if (dir[SPEC] == 1)
				i += to_s(&buf[i], dir, ap);
			else if (dir[SPEC] > 1 && dir[SPEC] < 9)
				i += to_nbr(&buf[i], dir, ap);
		}
		if (*(*format - 1) == '\n')
			return (i);
	}
	return (i);
}

// int			ft_printf(const char *format, ...)
// {
// 	char	buf[BUFF_SIZE];
// 	va_list	ap;
// 	int		printed;
// 	int		last;
//
// 	if (format == NULL)
// 		return (-1);
// 	printed = 0;
// 	va_start(ap, format);
// 	while (*format)
// 	{
// 		last = ft_cont(buf, &format, ap, 0);
// 		write(1, buf, last);
// 		printed += last;
// 	}
// 	va_end(ap);
// 	return (printed);
// }

int			ft_fprintf(int fd, const char *format, ...)
{
	char	buf[BUFF_SIZE];
	va_list	ap;
	int		printed;
	int		last;

	if (format == NULL)
		return (-1);
	printed = 0;
	va_start(ap, format);
	while (*format)
	{
		last = ft_cont(buf, &format, ap, 0);
		write(fd, buf, last);
		printed += last;
	}
	va_end(ap);
	return (printed);
}
