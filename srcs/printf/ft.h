/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 16:51:55 by frlindh           #+#    #+#             */
/*   Updated: 2020/02/17 13:46:32 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_H
# define FT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

# define BUFF_SIZE 10241
# define C_SPEC "cspdiuxX%n"
# define NULLSTR "(null)"

# define ZERO 0
# define LEFT 1
# define PLUS 2
# define SPACE 3
# define SMALL 4
# define S 5
# define LONG 6
# define SHORT 7
# define WIDTH 8
# define PREC 9
# define SPEC 10

// int		ft_printf(const char *format, ...);
int		ft_fprintf(int fd, const char *format, ...);
int		ft_strnlen(char *str, int n);
int		skip_atoi(const char **s);
int		to_c(char *buf, int *dir, va_list ap);
int		to_s(char *buf, int *dir, va_list ap);
int		to_nbr(char *buf, int *dir, va_list ap);
void	to_n(int i, int *dir, va_list ap);

#endif
