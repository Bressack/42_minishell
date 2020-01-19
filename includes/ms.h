/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 15:53:10 by tharchen          #+#    #+#             */
/*   Updated: 2020/01/19 14:16:34 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_H
# define MS_H
# include <double_linked.h>
# include <get_next_line.h>
# include <try_malloc.h>
# include <utils.h>
# include <color_shell.h>
# define PROMPT_ARROW	"➜"
typedef struct			s_sep
{
	char				*str;
}						t_sep;
typedef struct			s_cmd // sep by cmd_sep
{
	struct s_cmd		*next;
	struct s_cmd		*prev;
	char				*path;
	char				**av;
}						t_cmd;
typedef struct			s_exp // sep by exp_sep
{
	struct s_exp		*next;
	struct s_exp		*prev;
	t_cmd				*cmd;
	t_cmd_sep			*sep;
}						t_exp;
#endif
