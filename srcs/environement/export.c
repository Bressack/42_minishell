/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 17:47:16 by fredrika          #+#    #+#             */
/*   Updated: 2020/03/02 19:23:12 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	print_exp(void)
{
	t_env	*trav;

	trav = g_env;
	while (trav)
	{
		if (trav->export == 1)
		{
			ft_dprintf(STDOUT_FILENO, "declare -x %s", trav->name);
			if (trav->value)
				ft_dprintf(STDOUT_FILENO, "=\"%s\"", trav->value);
			write(STDOUT_FILENO, "\n", 1);
		}
		trav = trav->next;
	}
	return (0);
}

/*
** [IF] THE ENV VAR ALREADY EXISTS -> either replace if def value // nothing
** [ELSE] IF THE ENV DOESN'T EXIST: ADD BACK -- with value if = otherwise NULL
*/

void		set_var(char *name, int op, char *val, int export)
{
	t_env	*trav;

	if ((trav = ret_env(name)) != NULL)
	{
		(op == '+') ? trav->value = cat_value(trav->value, val) : 0;
		if (op == '=')
		{
			mfree(trav->value);
			trav->value = ft_strdup(val);
		}
		trav->export = 1;
	}
	else
	{
		trav = g_env;
		while (trav && trav->next)
			trav = trav->next;
		if (!((trav->next) = (t_env *)mmalloc(sizeof(t_env))))
			return ;
		(trav->next)->name = ft_strdup(name);
		(trav->next)->value = (op == 0) ? NULL : ft_strdup(val);
		(trav->next)->next = NULL;
		(trav->next)->export = export;
	}
}

int			export(int ac, char **av)
{
	int		i;
	int		j;
	int		op;
	int		export;
	char	cpy[LINE_MAX]; //secure for over ?

	export = (ft_strcmp(av[0], "export")) ? 0 : 1;
	if ((i = -1) < 0 && export && ac == 1)
		return (print_exp());
	while (++i < ac && (j = -1) == -1)
	{
		if (av[i] && ((*av[i] >= '0' && *av[i] <= '9') || !ok_envchar(*av[i])))
			bi_error(av[0], av[i], "not a valid identifier", 1);
		else if (av[i])
		{
			while (*av[i] && *av[i] != ' ' && *av[i] != '+' && *av[i] != '=')
				cpy[++j] = *av[i]++;
			if ((op = *av[i]) != 0 && *av[i]++ == '+' && *av[i] != '=')
				bi_error(av[0], av[i], "not a valid identifier", 1);
			else if ((cpy[++j] = '\0') == '\0')
				(op == '+') ? set_var(cpy, op, ++av[i], export) :
				set_var(cpy, op, av[i], export);
		}
	}
	return (0);
}
