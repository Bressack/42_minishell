/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 16:51:55 by frlindh           #+#    #+#             */
/*   Updated: 2020/02/22 00:37:27 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF
# define FT_PRINTF

// # include <minishell.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

# define PF_BUFF_SIZE 16384
# define C_SPEC "cspdiuxX%n"
# define NULLSTR "(null)"

typedef enum		e_ft_printf_dir
{
	ZERO,
	LEFT,
	PLUS,
	SPACE,
	SMALL,
	S,
	LONG,
	SHORT,
	WIDTH,
	PREC,
	SPEC
}					t_ft_printf_dir;

int		ft_printf(const char *format, ...);
int		ft_dprintf(int fd, const char *format, ...);
int		ft_strnlen(char *str, int n);
int		skip_atoi(const char **s);
int		to_c(char *buf, int *dir, va_list ap);
int		to_s(char *buf, int *dir, va_list ap);
int		to_nbr(char *buf, int *dir, va_list ap);
void	to_n(int i, int *dir, va_list ap);

#endif