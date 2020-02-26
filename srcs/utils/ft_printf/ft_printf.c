/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 10:37:08 by frlindh           #+#    #+#             */
/*   Updated: 2020/02/26 04:22:03 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

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
			dir[PRINTF_LONG]++;
		if (**format == 'h')
			dir[PRINTF_SHORT]++;
		(*format)++;
	}
	(dir[PRINTF_SPEC] = ft_iscspec(**format)) >= 0 ? (*format)++ : 0;
	if (dir[PRINTF_SPEC] == 9)
		to_n(i, dir, ap);
}

static void	ft_initdir(int *dir, const char **f, va_list ap)
{
	while (**f == '+' || **f == '-' || **f == '.' || **f == '#' || **f == ' ' ||
	**f == '\'' || (**f >= '0' && **f <= '9'))
	{
		dir[PRINTF_ZERO] = (**f == '0') ? 1 : dir[PRINTF_ZERO];
		dir[PRINTF_LEFT] = (**f == '-') ? 1 : dir[PRINTF_LEFT];
		dir[PRINTF_PLUS] = (**f == '+') ? 1 : dir[PRINTF_PLUS];
		dir[PRINTF_SPACE] = (**f == ' ') ? 1 : dir[PRINTF_SPACE];
		dir[PRINTF_S] = (**f == '#') ? 1 : dir[PRINTF_S];
		if (**f == '.' && (*f)++ && (dir[PRINTF_PREC] = 0) == 0)
		{
			if (**f >= '0' && **f <= '9')
				dir[PRINTF_PREC] = skip_atoi(f);
			else if (**f == '*' && (*f)++ && (dir[PRINTF_PREC] = va_arg(ap, int)) < 0)
				dir[PRINTF_PREC] = -dir[PRINTF_PREC];
		}
		else if (**f >= '1' && **f <= '9')
			dir[PRINTF_WIDTH] = skip_atoi(f);
		else if (**f == '*' && (*f)++ && (dir[PRINTF_WIDTH] = va_arg(ap, int)) < 0)
		{
			dir[PRINTF_LEFT] = 1;
			dir[PRINTF_WIDTH] = -dir[PRINTF_WIDTH];
		}
		else
			(*f)++;
	}
}

static int	ft_cont(char *buf, const char **format, va_list ap, int i)
{
	int		dir[11];
	int		j;

	while (**format && i < PF_BUFF_SIZE - 65)
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
			if (dir[PRINTF_SPEC] < 1 || dir[PRINTF_SPEC] == 8)
				i += to_c(&buf[i], dir, ap);
			else if (dir[PRINTF_SPEC] == 1)
				i += to_s(&buf[i], dir, ap);
			else if (dir[PRINTF_SPEC] > 1 && dir[PRINTF_SPEC] < 9)
				i += to_nbr(&buf[i], dir, ap);
		}
		if (*(*format - 1) == '\n')
			return (i);
	}
	return (i);
}

int			ft_printf(const char *format, ...)
{
	char	buf[PF_BUFF_SIZE];
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
		write(1, buf, last);
		printed += last;
	}
	va_end(ap);
	return (printed);
}

int			ft_dprintf(int fd, const char *format, ...)
{
	char	buf[PF_BUFF_SIZE];
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
