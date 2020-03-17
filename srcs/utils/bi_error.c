/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 10:32:31 by frlindh           #+#    #+#             */
/*   Updated: 2020/03/12 17:16:46 by frlindh          ###   ########.fr       */
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
	ft_dprintf(2, "minishell: %s: ", ft);
	if (arg != NULL)
		f == 1 ? ft_dprintf(2, "`%s\': ", arg) : ft_dprintf(2, "%s: ", arg);
	if (mess)
		ft_dprintf(2, "%s\n", mess);
	else
	{
		if (f == 127)
			ft_dprintf(2, "No such file or directory\n");
		else if (f == 124 && (f += 2))
			ft_dprintf(2, "File name too long\n");
		else if (f == 128 && f--)
			ft_dprintf(2, "command not found\n");
		else if (f == 126)
			ft_dprintf(2, "Permission denied\n");
		else if (f++)
			ft_dprintf(2, "Is a directory\n");
		return (f);
	}
	return (1);
}
