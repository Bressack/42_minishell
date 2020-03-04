/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 17:47:16 by fredrika          #+#    #+#             */
/*   Updated: 2020/03/04 11:42:31 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	print_exp(int out)
{
	t_env	*trav;

	trav = g_env;
	while (trav)
	{
		if (trav->export == 1)
		{
			ft_dprintf(out, "declare -x %s", trav->name);
			if (trav->value)
				ft_dprintf(out, "=\"%s\"", trav->value);
			write(out, "\n", 1);
		}
		trav = trav->next;
	}
	return (0);
}

/*
** [IF] THE ENV VAR ALREADY EXISTS -> replace if def value || make sure export == 1 || nothing
** [ELSE] IF THE ENV DOESN'T EXIST: ADD BACK -- with value if = otherwise NULL
*/

void		set_var(char *name, int op, char *val, int export)
{
	t_env	**trav;
	t_env	*set;

	if ((set = ret_env(name)))
	{
		(op == '+') ? set->value = cat_value(set->value, val) : 0;
		if (op == '=')
		{
			mfree(set->value);
			set->value = ft_strdup(val);
		}
		if (export == 1)
			set->export = 1;
	}
	else
	{
		trav = &g_env;
		while (*trav)
			trav = &((*trav)->next);
		(*trav) = (t_env *)mmalloc(sizeof(t_env));
		(*trav)->name = ft_strdup(name);
		(*trav)->value = (op == 0) ? NULL : ft_strdup(val);
		(*trav)->next = NULL;
		(*trav)->export = export;
	}
}

/*
** EXPORT CAN BE CALLED EITHER WITH EXPORT OR JUST WITH ASSIGNMENTS
** SO "export C=1 B=2" AND "C=1 B=2" ARE BOTH OKAY. IF CALLED WITH ONLY
** "export" IT WILL PRINT WITH print_exp(). IF AN ASSIGNMENT START WITH AN
** INVALID CHAR OR IF IT'S C+3 ---> ERRMESS AND SKIP. OTHERWISE IT WILL
** CALL SET VAR WITH CPY(=NAME), THE OPERATOR(='+' || '=' || 0) AND THE
** VALUE TO BE SET.
*/

int			export(int ac, char **av, int out)
{
	int		i;
	int		j;
	int		op;
	int		export;
	char	cpy[LINE_MAX];

	export = (ft_strcmp(av[0], "export")) ? 0 : 1;
	if ((i = -1) == -1 && export && i++ && ac == 1)
		return (print_exp(out));
	while (++i < ac && (j = -1) == -1)
	{
		if (av[i] && ((*av[i] >= '0' && *av[i] <= '9') || !ok_envchar(*av[i])))
			bi_error(av[0], av[i], "not a valid identifier", 1);
		else if (av[i])
		{
			while (*av[i] && *av[i] != ' ' && *av[i] != '+' && *av[i] != '=')
				(j < LINE_MAX) ? cpy[++j] = *av[i]++ : i++;
			if ((op = *av[i]) != 0 && *av[i]++ == '+' && *av[i] != '=')
				bi_error(av[0], av[i], "not a valid identifier", 1);
			else if ((cpy[++j] = '\0') == '\0')
				(op == '+') ? set_var(cpy, op, ++av[i], export) :
				set_var(cpy, op, av[i], export);
		}
	}
	return (0);
}
