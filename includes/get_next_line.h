/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 09:07:42 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/25 14:22:35 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
// # define GNL_RET 0
// # define GNL_LEN 1
# define GNL_BUFFER_SIZE 4096 + 1

# include <minishell.h>

// int		get_next_line(const int fd, char **line);
int			get_next_line(int fd, char **line);
// int			get_next_line(int fd, t_lexer *lex);
#endif
