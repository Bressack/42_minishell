/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 11:20:01 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/01 14:39:58 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <libc.h>
# include <errno.h>
# include <color_shell.h>
# include <try_malloc.h>
# include <mmalloc.h>
# include <double_linked.h>
# include <utils.h>
# include <class__token.h>
# include <class__lexer.h>
# include <ast_builder.h>
# include <get_next_line.h>
# include <ft_printf.h>
# include <env.h>
# include <commands.h>
void		tree_draw(t_node *node);
#endif
