/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 01:48:59 by fredrika          #+#    #+#             */
/*   Updated: 2020/02/21 20:30:53 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct	s_env
{
	char			*name;
	char			**value;
	struct s_env	*next;
}				t_env;

t_env	*g_env;

void	print_env();
char	**ret_env(char *name);
char	*ft_copsep(char **e, char sep);
void	set_env(t_env *e, char *env);
void	get_env(int ac, char **av, char **env);
void	env_destructor(t_env *f, int flag);
void	export(char *val);
void	unset(char *name);

#endif
