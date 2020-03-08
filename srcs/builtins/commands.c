/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 11:59:36 by frlindh           #+#    #+#             */
/*   Updated: 2020/03/08 13:36:52 by fredrikalindh    ###   ########.fr       */
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

	ft_dprintf(out, "exit\n");
	code = g_exit;
	if (ac > 1 && !ft_strisnum(args[1]) && (code = 2))
		bi_error(args[0], args[1], "numeric argument required", 0);
	else if (ac > 2 && bi_error(args[0], NULL, "too many arguments", 0))
		return (1);
	(ac == 2 && code == 0) ? code = ft_atoi(args[1]) : 0;
	free_all_malloc();
	out == -1 ? code = 0 : 0;
	exit(code);
}

int		xcd(int ac, char **args, int out)
{
	t_env	*slct;
	char	*tmp;
	char	*tmp2;
	char	dir[LINE_MAX];

	slct = ret_env("OLDPWD");
	tmp = (slct) ? slct->value : NULL;
	getcwd(dir, LINE_MAX);
	if (ac > 2)
		return (bi_error(args[0], NULL, "too many arguments", 0));
	if (ac == 1 && (tmp2 = ret_envval("HOME")))
		chdir(tmp2);
	else if (ac == 1 || (args[1][0] == '-' && !tmp))
		return (ac != 1) ? (bi_error(args[0], NULL, "OLDPWD not set", 0)) :
			(bi_error(args[0], NULL, "HOME not set", 0));
	else if (args[1][0] == '-' && tmp && ft_dprintf(out, "%s\n", tmp))
		chdir(tmp);
	else if (chdir(args[1]) != 0)
		return (bi_error(args[0], args[1], strerror(errno), 0));
	if (slct)
		slct->value = (ret_envval("PWD")) ? ret_envval("PWD") : ft_strdup(dir);
	if ((slct = ret_env("PWD")))
		slct->value = ft_strdup(getcwd(dir, LINE_MAX));
	mfree((void **)&tmp);
	return (0);
}
