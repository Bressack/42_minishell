/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 19:07:19 by fredrika          #+#    #+#             */
/*   Updated: 2020/03/10 22:06:06 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include <minishell.h>
# define BUILTINS 7

unsigned int	g_exit;
typedef enum	e_err_value
{
	ERROR,
	SUCCESS
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
/*
** EXECUTE
*/
char			**check_cmd(t_node *cmd, int *ac, int *type);
int				launch(t_node *cmd, char **av);
int				execute_fork(t_node *cmd);
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
