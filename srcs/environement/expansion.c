/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 15:17:15 by frlindh           #+#    #+#             */
/*   Updated: 2020/03/05 02:55:41 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** ALLOWED CHARACTERS TO FOLLOW A $. MIGHT BE BETTER CHANGING TO JUST
** ALLOWED CHARACTERS IN VARIABLE + ? <---
*/

int		ok_envchar(char c) //FUNCTION TO CHECK NAMES --- TO BE UPDATED ---
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' ||
			(c >= '0' && c <= '9') || c == '@' || c == '*' || c == '#' ||
			c == '-' || c == '!' || c == '?' || c == '{' || c == '('); //
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
** EXPANDING ENV VAR, SKIPPING CURLY BRACKETS IF ${NAME}
*/

int		expand_env(char **args, char *new)
{
	char	*val;
	int		i;
	int		curl;
	char	name[LINE_MAX];

	i = -1;
	curl = 0;
	while ((*args)[++i] && (ok_envchar((*args)[i]) || (*args)[i] == '}'))
		if ((*args)[i] == '{' || (*args)[i] == '}')
			curl = ((*args)[i] == '{') ? curl + 1 : curl - 1;
	(**args == '{' && curl == 0) ? (*args)++ : 0;
	i = 0;
	while (**args && ok_envchar(**args)) // ADD SAFETY FOR NAME ?
		name[i++] = *((*args)++);
	(**args == '}' && curl == 0) ? (*args)++ : 0;
	name[i] = '\0';
	val = ret_envval(name);
	i = 0;
	while (val && val[i])
	{
		new[i] = val[i];
		i++;
	}
	new[i] = '\0';
	!ft_strcmp(name, "?") ? mfree(val) : 0;
	return (i);
}

/*
** SPECIAL CHARS FOR \ ---> the bashslash wont be printed
*/

int		spec_char(char c)
{
	return (c == '\\' || c == '$' || c == '\"' || c == '`');
}

/*
** EXPAND QUOTE ITERATES AN ENTIRE ARG GIVEN BY LEXER, MEANING EITHER IT HAS
** THE QUOTES SAVED. A SINGLE QUOTE ' WILL PRESERVE EVERY CHARACTER INSIDE
** WHICH IS WHY IT HAS IT'S OWN WHILE LOOP
** A DOUBLE QUOTE " WILL STILL EXPAND $ UNLESS IT IS QUOTED BY A BACKSLASH \
** THE BACKSLASH IS PRINTED WITH NORMAL CHARS IF INSIDE QUOTES AND REMOVED
** OUTSIDE FOR ALL.
** A TILDE WILL BE EXPANDED TO THE HOME VAR IF SET
** "$HOME $RAND \$HOME" ---> [Users/frlindh  $HOME]
** '$HOME \\' ---> [$HOME \\]
** echo \t \\ \$HOME "~ \t \\ \$HOME" ---> [t \ $HOME Users/frlindh \t \ $HOME]
*/
char	*expand_qt(char *args)
{
	int		quote;
	int		j;
	char	new[LINE_MAX];

	quote = 0;
	j = 0;
	while (args && *args)
	{
		if (quote == 0 && *args == '\'')
			while (args++ && *args && *args != '\'')
				new[j++] = *args;
		else if (*args == '$' && ok_envchar(*(args + 1)) && args++)
			j += expand_env(&args, &new[j]);
		else if (*args == '\"' && args++)
			quote = (quote == 0) ? *args : 0;
		else if (*args == '\\' &&
		(((quote == 0 || spec_char(*(args + 1))) && args++) || 1))
			new[j++] = *args++;
		else if (quote == 0 && *args == '~' && args++)
			j += tilde_exp(&new[j]);
		else
			new[j++] = *args++;
	}
	new[j] = '\0';
	//mfree
	return (j > 0) ? (ft_strdup(new)) : NULL;
}

/*
** EXPAND AND SPLIT: IF AN ENVIRONMENT VAR IS EXPANDED OUTSIDE QUOTES IT
** WILL BE SPLIT BY \t\n and space OR BY IFS IF SET. IF RETURN BY EXPAND QT
** IS NULL IT WILL NOT KEEP ARGUMENT. AFTER SPLIT IT INSERTS IN LIST
*/

void	expand_split_env(t_token **args, int *ac)
{
	t_token	*next;
	char	**arr;
	char	*ifs;
	int		i;

	if (!((*args)->value = expand_qt((*args)->value)))
	{
		*args = (*args)->next;
		return ;
	}
	ifs = ret_envval("IFS");
	arr = ifs ? ft_split((*args)->value, ifs) : ft_split((*args)->value, IFS);
	if (!(*arr) && (*args = ((*args)->next)))
		return ;
	(*args)->value = arr[0];
	next = (*args)->next;
	i = 0;
	while (*ac++ != -1 && arr[++i])
	{
		(*args)->next = (t_token *)mmalloc(sizeof(t_token));
		((*args)->next)->value = arr[i];
		args = &((*args)->next);
	}
	(*args)->next = next;
}

/*
** START OF EXPANSION:
** IF first char is a $ it will call expand and split env
** ELSE it will call only expand. Meaning if LS="     ls     -l"
** $LS ---> [ls] [-l] && "$LS" ---> [     ls     -l]
*/
int		expand(t_token **args)
{
	int	ac;

	ac = 0;
	while (*args)
	{
		if ((*args)->value[0] == '$' && ok_envchar((*args)->value[1]))
			expand_split_env(args, &ac);
		else if (++ac != -1)
		{
			(*args)->value = expand_qt((*args)->value);
			(!(*args)->value) ? (*args)->value = ft_strdup("") : 0;
			args = &((*args)->next);
		}
	}
	return (ac);
}
