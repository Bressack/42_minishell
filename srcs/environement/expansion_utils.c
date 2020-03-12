/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 21:56:27 by fredrika          #+#    #+#             */
/*   Updated: 2020/03/12 18:17:18 by frlindh          ###   ########.fr       */
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

int		expand_simple_quotes(char **args, char *new)
{
	int		i;

	i = 0;
	(*args)++;
	while (*args && **args && **args != '\'')
		new[i++] = *((*args)++);
	(*args)++;
	return (i);
}
