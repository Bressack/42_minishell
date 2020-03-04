/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 16:51:55 by frlindh           #+#    #+#             */
/*   Updated: 2020/03/04 12:26:29 by frlindh          ###   ########.fr       */
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
	PF_ZERO,
	PF_LEFT,
	PF_PLUS,
	PF_SPACE,
	PF_SMALL,
	PF_S,
	PF_LONG,
	PF_SHORT,
	PF_WIDTH,
	PF_PREC,
	PF_SPEC
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
