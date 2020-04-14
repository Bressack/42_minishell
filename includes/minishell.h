/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 11:20:01 by tharchen          #+#    #+#             */
/*   Updated: 2020/04/14 12:14:34 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <limits.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>

# include <color_shell.h>
# include <mmalloc.h>
# include <get_next_line.h>
# include <ft_printf.h>
# include <double_linked.h>
# include <utils.h>
# include <class__token.h>
# include <class__lexer.h>
# include <ast_builder.h>
# include <ast_interpreter.h>
# include <env.h>
# include <commands.h>

int		g_reset;

typedef enum		e_optsignal
{
	CONTINUE,
	NOMATCH
}					t_optsignal;
void				tree_draw(t_node *node);
#endif
