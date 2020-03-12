/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 15:17:15 by frlindh           #+#    #+#             */
/*   Updated: 2020/03/12 20:09:13 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** EXPANDING ENV VAR
*/

int		expand_env(char **args, char *new)
{
	char	*val;
	int		i;
	char	name[LINE_MAX];

	i = 0;
	while (**args && ok_envchar(**args, 1))
	{
		if (i < LINE_MAX)
			name[i++] = *((*args)++);
		else
			(*args)++;
		if (name[i - 1] == '?')
			break ;
	}
	name[i] = '\0';
	val = ret_envval(name);
	i = 0;
	while (val && val[i])
	{
		new[i] = val[i];
		i++;
	}
	new[i] = '\0';
	!ft_strcmp(name, "?") ? mfree((void **)&val) : 0;
	return (i);
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

char	*expand_qt2(char *args, char *new)
{
	int		quote;
	int		j;

	quote = 0;
	j = 0;
	while (args && *args && j < 10000)
	{
		if (quote == 0 && *args == '\'')
			j += expand_simple_quotes(&args, &new[j]);
		else if (*args == '$' && ok_envchar(*(args + 1), 0) && args++)
			j += expand_env(&args, &new[j]);
		else if (*args == '\"' && args++)
			quote = (quote == 0) ? *args : 0;
		else if (*args == '\\' &&
		(((quote == 0 || spec_char(*(args + 1))) && args++) || 1))
			new[j++] = *args++;
		else if (quote == 0 && *args == '~' && *(args - 1) != '$' && args++)
			j += tilde_exp(&new[j]);
		else
			new[j++] = *args++;
	}
	new[j] = '\0';
	return (args);
}

char	*expand_qt(char *args)
{
	char	*prev;
	char	*ret;
	int		bufsize;

	bufsize = 20000;
	ret = NULL;
	while (args && *args)
	{
		prev = mmalloc(bufsize);
		if ((args = expand_qt2(args, prev)) && *args)
			ret = cat_value(ret, 0, prev);
	}
	ret = cat_value(ret, 0, prev);
	return (ret);
}

/*
** EXPAND AND SPLIT: IF AN ENVIRONMENT VAR IS EXPANDED OUTSIDE QUOTES IT
** WILL BE SPLIT BY \t\n and space OR BY IFS IF SET. IF RETURN BY EXPAND QT
** IS NULL IT WILL NOT KEEP ARGUMENT. AFTER SPLIT IT INSERTS IN LIST
*/

t_token	**expand_split_env(t_token **args, int *ac)
{
	t_token	*next;
	char	**arr;
	char	*ifs;
	int		i;

	if (!((*args)->value = expand_qt((*args)->value)) || !*((*args)->value))
	{
		*args = ((*args)->next);
		return (*args) ? (&(*args)) : (NULL);
	}
	ifs = ret_envval("IFS");
	arr = (ifs) ? ft_split((*args)->value, ifs) : ft_split((*args)->value, IFS);
	if (!(*arr) && (*args = ((*args)->next)))
		return (&(*args));
	(*args)->value = arr[0];
	next = (*args)->next;
	i = 0;
	while ((*ac += 1) > 0 && arr[++i] != NULL)
	{
		(*args)->next = (t_token *)mmalloc(sizeof(t_token));
		((*args)->next)->value = arr[i];
		args = &((*args)->next);
	}
	(*args)->next = next;
	return (&((*args)->next));
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
	while (args && *args)
	{
		if ((*args)->value[0] == '$' && ok_envchar((*args)->value[1], 0))
			args = expand_split_env(args, &ac);
		else if (ac++ != -1)
		{
			(*args)->value = expand_qt((*args)->value);
			(!(*args)->value) ? (*args)->value = ft_strdup("") : 0;
			args = &((*args)->next);
		}
	}
	return (ac);
}
