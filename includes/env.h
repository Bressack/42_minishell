/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 01:48:59 by fredrika          #+#    #+#             */
/*   Updated: 2020/03/10 22:01:41 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <minishell.h>

typedef struct	s_env
{
	char			*name;
	char			*value;
	unsigned int	export:2;
	struct s_env	*next;
}				t_env;

extern t_env	*g_env;
/*
** ENV.C
*/
int				print_env(int ac, char **args, int out);
t_env			*ret_env(char *name);
char			*ret_envval(char *name);
int				set_env(t_env *e, char *env);
void			get_env(int ac, char **av, char **env);
/*
** EXPORT.C
*/
int				export(int ac, char **args, int out);
void			set_var(char *name, int op, char *val, int export);
/*
** UNSET.C
*/
int				unset(int ac, char **args, int out);
/*
** EXPANSION_UTILS
*/
int				is_valid_variable(char *args, int flag);
int				ok_envchar(char c, int f);
char			**convert_to_arr(t_token *args, int ac);
int				tilde_exp(char *new);
int				spec_char(char c);
/*
** EXPANSION
*/
# define IFS " \t\n"
int				expand(t_token **args);


#endif
