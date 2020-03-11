/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 21:56:27 by fredrika          #+#    #+#             */
/*   Updated: 2020/03/11 20:09:02 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** SPECIAL CHARS FOR \ ---> the bashslash wont be printed
*/

int		spec_char(char c)
{
	return (c == '\\' || c == '$' || c == '\"' || c == '`');
}

/*
** F==0: ALLOWED CHARACTERS TO FOLLOW A $. F==1: ALLOWED CHARACTERS IN ENV + ?
*/

int		ok_envchar(char c, int f)
{
	if (f == 1)
		return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' ||
			(c >= '0' && c <= '9') || c == '?');
	else
		return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' ||
		c == '?');
}

int		is_valid_variable(char *args, int flag)
{
	int i;

	i = -1;
	if (!args)
		return (0);
	if (!(is_letter(args[0])) && args[0] != '_')
		return (0);
	while (args[++i] && (flag == 0 || (args[i] != '=' &&
	!(args[i] == '+' && args[i + 1] == '='))))
		if (!(is_letter(args[i])) && args[i] != '_' && !(is_num(args[i])))
			return (0);
	if (flag == 2 && args[i] != '=')
		return (0);
	return (1);
}

int		tilde_exp(char *new)
{
	char	*home;
	int		i;

	home = ret_envval("HOME");
	i = 0;
	if (!home)
		new[i++] = '~';
	while (home && *home)
		new[i++] = *home++;
	return (i);
}

/*
** JUST TO CONVERT THE LIST OF ARGS TO ARRAY
*/

char	**convert_to_arr(t_token *args, int ac)
{
	char	**av;
	t_token	*prev;
	int		i;

	av = (char **)mmalloc(sizeof(char *) * (ac + 1));
	i = 0;
	while (args)
	{
		av[i++] = args->value;
		prev = args;
		args = args->next;
	}
	av[i] = NULL;
	return (av);
}
