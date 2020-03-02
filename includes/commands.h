/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 19:07:19 by fredrika          #+#    #+#             */
/*   Updated: 2020/03/02 05:24:33 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

#include <minishell.h>
#define BUILTINS 7
// #define STDOUT 1
// #define STDERR 2
// #define STDIN 2

int		xecho(int argc, char **args);
int		xpwd(int argc, char **args);
int		xexit(int argc, char **args);
int		xcd(int argc, char **args);
int		launch(t_node *cmd, char **av);
int		execute(t_node *cmd);
// int		execute(int ac, char **args);

typedef struct		s_bi
{
	char	*name;
	int		(*f)(int argc, char	**args); //change to const ?
}					t_bi;

#endif
