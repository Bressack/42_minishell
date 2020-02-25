/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 17:47:16 by fredrika          #+#    #+#             */
/*   Updated: 2020/02/25 14:13:08 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		print_exp(void)
{
	t_env	*trav;
	int		i;

	trav = g_env;
	while (trav)
	{
		i = 0;
		ft_dprintf(1, "declare -x %s", trav->name);
		if (trav->value)
			ft_dprintf(1, "=\"%s\"", trav->value);
		write(1, "\n", 1);
		trav = trav->next;
	}
	return (0);
}

char	*ft_copsep(char **e, char sep)
{
	int		i;
	char	*ret;
	int		inqt;

	i = 0;
	while (e && e[0][i] && e[0][i] != ' ' && e[0][i] != sep)
		i++;
	if (!(ret = (char *)malloc(i + 1)))
		return (NULL);
	i = 0;
	inqt = 0;
	while (**e && **e != sep && (**e != ' ' || inqt != 0))
	{
/*
** 		NOT SURE IF THIS IS A GOOD PLACE TO HANDLE QUOTES THOUGH
*/
		if (**e == '\"' || **e == '\'')
		{
			if (inqt == 0 || inqt % **e != 0)
				inqt += **e;
			else
				inqt -= **e;
			(*e)++;
		}
		ret[i] = *((*e)++);
		(sep == '=' && ret[i] == '+') ? 0 : i++; //for not copying + & =
	}
	ret[i] = '\0';
	(**e == sep) ? (*e)++ : 0;
	return (ret);
}

void	export(char *val)
{
	t_env	*trav;
	t_env	*new;
	int		i;
	char	cpy[50];

/*
** HOPEFULLY CAN REMOVE THE SKIP WHITESPACES LATER BC ALREADY REMOVED IN LEXER
*/
	while (val && *val && *val == ' ')
		val++;
	if ((i = -1) == -1 && (val == NULL || *val == '\0') && !print_exp())
		return ;
	while (val[++i] && val[i] != ' ' && val[i] != '=' && val[i] != '+')
		cpy[i] = val[i];
/*
** 	IF THE ENV VAR ALREADY EXISTS -> either replace if def value // nothing
*/
	if ((cpy[i] = '\0') == '\0' && (trav = ret_env(cpy)) != NULL)
	{
		val += i;
		if (*val == '+' && *(++val) == '=' && val++)
			trav->value = cat_value(trav->value, ft_copsep(&val, '\n'));
		else if (*val == '=' && val++)
		{
			free(trav->value);
			trav->value = ft_copsep(&val, '\n');
		}
	}
/*
** 	IF THE ENV DOESN'T EXIST: ADD BACK -- with value if = otherwise NULL
*/
	else
	{
		trav = g_env;
		while (trav && trav->next)
			trav = trav->next;
		if (!(new = (t_env *)malloc(sizeof(t_env))))
			return ;
		new->name = ft_copsep(&val, '=');
		new->value = (*(val - 1) == '=') ? ft_copsep(&val, '\n') : NULL;
		new->next = trav->next;
		trav->next = new;
	}
	while (*val && *val == ' ')
		val++;
/*
** 	RECURSIVE TO TAKE CARE ON MULTIPLE
*/
	if (*val)
		export(val);
}