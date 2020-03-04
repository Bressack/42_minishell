/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 19:07:19 by fredrika          #+#    #+#             */
/*   Updated: 2020/03/04 11:45:33 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

#include <minishell.h>
#define BUILTINS 7

unsigned int	g_exit;
/*
** COMMANDS
*/
int		xecho(int argc, char **args, int out);
int		xpwd(int argc, char **args, int out);
int		xexit(int argc, char **args, int out);
int		xcd(int argc, char **args, int out);

/*
** EXECUTE
*/
// int		launch(t_node *cmd, char **av);
int		launch(t_node *cmd, char **av);
int		execute(t_node *cmd);

/*
** PATH.C
*/
char	*get_path(char *command);

typedef struct		s_bi
{
	char	*name;
	int		(*f)(int argc, char	**args, int out);
}					t_bi;

#endif
