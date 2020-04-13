/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 19:07:19 by fredrika          #+#    #+#             */
/*   Updated: 2020/04/13 14:04:01 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include <minishell.h>
# define BUILTINS 7

unsigned int	g_exit;
typedef enum	e_err_value
{
	SUCCESS,
	ERROR,
	EMPTY
}				t_err_value;
/*
** COMMANDS
*/
int				xecho(int argc, char **args, int out);
int				xpwd(int argc, char **args, int out);
int				xexit(int argc, char **args, int out);
int				xcd(int argc, char **args, int out);

/*
** EXECUTE_UTILS
*/
char			**env_to_arr(t_env *trav);
void			sig_exec(int signo);
char			**convert_to_arr(t_token *args, int ac);
/*
** EXECUTE
*/
char			**check_cmd(t_node *cmd, int *ac, int *type);
int				launch(t_node *cmd, char **av);
int				execute_fork(t_node *cmd, int out);
int				execute_simple(t_node *cmd);
/*
** PATH.C
*/
char			*get_path(char *command, int *err);

typedef struct	s_bi
{
	char	*name;
	int		(*f)(int argc, char	**args, int out);
}				t_bi;

#endif
