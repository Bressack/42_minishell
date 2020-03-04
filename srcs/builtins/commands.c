/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 11:59:36 by frlindh           #+#    #+#             */
/*   Updated: 2020/03/04 11:47:43 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		xecho(int ac, char **args, int out)
{
	int n;
	int i;

	n = 0;
	if (ac > 1)
	{
		i = 1;
		while (ft_strcmp(args[i], "-n") == 0 && i++ > 0)
			n = 1;
		while (i < ac)
		{
			ft_dprintf(out, "%s", args[i++]);
			if (i < ac)
				ft_dprintf(out, " ");
		}
	}
	if (n != 1)
		ft_dprintf(out, "\n");
	return (0);
}

int		xpwd(int ac, char **args, int out)
{
	char	cwd[LINE_MAX];

	(void)ac;
	(void)args;
	if (!(getcwd(cwd, LINE_MAX)))
		return (errno);
	ft_dprintf(out, "%s\n", cwd);
	return (0);
}

int		xexit(int ac, char **args, int out)
{
	int code;

	(void)out;
	ft_dprintf(1, "exit\n");
	code = g_exit; // set as LAST
	if (ac > 1 && !ft_isnum(args[1]) && (code = 2))
		bi_error(args[0], args[1], "numeric argument required", 0);
	else if (ac > 2 && bi_error(args[0], NULL, "too many arguments", 0))
		return (127);
	(ac == 2 && code == 0) ? code = ft_atoi(args[1]) : 0;
	free_all_malloc();
	exit(code);
}

int		xcd(int ac, char **args, int out)
{
	t_env	*change;
	char	*tmp;
	char	*tmp2;
	char	dir[LINE_MAX];

	(void)out;
	change = ret_env("OLDPWD");
	tmp = (change) ? change->value : NULL;
	if (ac > 2 && bi_error(args[0], NULL, "too many arguments", 0))
		return (2);
	if (ac == 1 && (tmp2 = ret_envval("HOME")))
		chdir(tmp2);
	else if (args[1][0] == '-' && tmp) // ADD ERR MESS
		chdir(tmp);
	else if (chdir(args[1]) != 0)
		return (bi_error(args[0], args[1], strerror(errno), 0));
	if (change)
		change->value = ret_envval("PWD"); // IF NOT SET MALLOC NEW
	if ((change = ret_env("PWD")))
	{
		getcwd(dir, LINE_MAX);
		change->value = ft_strdup(dir);
	}
	mfree(tmp);
	return (0);
}
