/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 19:07:19 by fredrika          #+#    #+#             */
/*   Updated: 2020/02/21 19:22:40 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

#include <minishell.h>
#define BUILTINS 7

void	xecho(char *args);
void	xpwd(char *args);
void	xexit(char *args);
void	xcd(char *args);

typedef struct		s_bi
{
	char	*name;
	int		len;
	void	(*f)(char	*args); //change to const ?
}					t_bi;

#endif
