/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 10:32:31 by frlindh           #+#    #+#             */
/*   Updated: 2020/02/26 11:44:10 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** TWO TYPES OF ERRMESS: 
** 	WITHOUT ARG: minishell: cd: too many arguments
** 	WITH	ARG: minishell: cd: xxx: No such file or directory
** 				 minishell: export: `5+H\': not a valid identifier
*/

int		bi_error(char *ft, char *arg, char *mess, int f)
{
	ft_dprintf(1, "minishell: %s: ", ft);
	if (arg != NULL)
		f == 1 ? ft_dprintf(1, "`%s\': ", arg) : ft_dprintf(1, "%s: ", arg);
	ft_dprintf(1, "%s\n", mess);
	return (1);
}