/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 10:37:08 by frlindh           #+#    #+#             */
/*   Updated: 2020/03/04 12:57:51 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static void	ft_specifier(int *dir, const char **format, int i, va_list ap) //DID A CHANGE TO MERGE FUNCTIONS SO HOPE IT STILL WORKS HAHA
{
	int		c;

	while (**format == 'h' || **format == 'l')
	{
		if (**format == 'l')
			dir[PF_LONG]++;
		if (**format == 'h')
			dir[PF_SHORT]++;
		(*format)++;
	}
	c = -1;
	while (C_SPEC[++c])
		if (C_SPEC[c] == **format)
			break ;
	if (!C_SPEC[c])
		c = -1;
	(dir[PF_SPEC] = c) >= 0 ? (*format)++ : 0;
	if (dir[PF_SPEC] == 9)
		to_n(i, dir, ap);
}

static void	ft_initdir(int *dir, const char **f, va_list ap)
{
	while (**f == '+' || **f == '*' || **f == '-' || **f == '.' || **f == '#'
	|| **f == ' ' || **f == '\'' || (**f >= '0' && **f <= '9'))
	{
		dir[PF_ZERO] = (**f == '0') ? 1 : dir[PF_ZERO];
		dir[PF_LEFT] = (**f == '-') ? 1 : dir[PF_LEFT];
		dir[PF_PLUS] = (**f == '+') ? 1 : dir[PF_PLUS];
		dir[PF_SPACE] = (**f == ' ') ? 1 : dir[PF_SPACE];
		dir[PF_S] = (**f == '#') ? 1 : dir[PF_S];
		if (**f == '.' && (*f)++ && (dir[PF_PREC] = 0) == 0)
		{
			if (**f >= '0' && **f <= '9')
				dir[PF_PREC] = skip_atoi(f);
			else if (**f == '*' && (*f)++ &&
			(dir[PF_PREC] = va_arg(ap, int)) < 0)
				dir[PF_PREC] = -dir[PF_PREC];
		}
		else if (**f >= '1' && **f <= '9')
			dir[PF_WIDTH] = skip_atoi(f);
		else if (**f == '*' && (*f)++ && (dir[PF_WIDTH] = va_arg(ap, int)))
			(dir[PF_WIDTH] < 0 && (dir[PF_LEFT] = 1)) ?
			dir[PF_WIDTH] = -dir[PF_WIDTH] : 0;
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
			if (dir[PF_SPEC] < 1 || dir[PF_SPEC] == 8)
				i += to_c(&buf[i], dir, ap);
			else if (dir[PF_SPEC] == 1)
				i += to_s(&buf[i], dir, ap);
			else if (dir[PF_SPEC] > 1 && dir[PF_SPEC] < 9)
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
