/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 11:59:36 by frlindh           #+#    #+#             */
/*   Updated: 2020/03/12 00:33:56 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		xecho(int ac, char **args, int out)
{
	int		n;
	int		i;

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
	char	*cwd2;

	(void)ac;
	(void)args;
	if (getcwd(cwd, LINE_MAX))
		ft_dprintf(out, "%s\n", cwd);
	else if ((cwd2 = ret_envval("PWD")))
		ft_dprintf(out, "%s\n", cwd2);
	else if ((cwd2 = ret_envval("OLDPWD")))
		ft_dprintf(out, "%s\n", cwd2);
	else
	{
		return (bi_error(args[0],
			"error retrieving current directory", strerror(errno), 0));
	}
	return (0);
}

int		xexit(int ac, char **args, int out)
{
	int		code;

	ft_dprintf(2, "exit\n");
	code = g_exit;
	if (ac > 1 &&
		(!ft_strisnum(args[1]) || ft_strlen(args[1]) > 11) && (code = 2))
		bi_error(args[0], args[1], "numeric argument required", 0);
	else if (ac > 2 && bi_error(args[0], NULL, "too many arguments", 0))
		return (code == 2) ? (2) : (1);
	(ac == 2 && code == 0) ? code = ft_atoi(args[1]) : 0;
	free_all_malloc();
	out == -1 ? code = 0 : 0;
	exit(code);
}

void	set_pwdenv(char *dir, int flag)
{
	char	dir2[LINE_MAX];
	t_env	*old;
	t_env	*pwd;

	pwd = ret_env("PWD");
	old = ret_env("OLDPWD");
	if (!old)
	{
		set_var("OLDPWD", '=', NULL, 0);
		old = ret_env("OLDPWD");
	}
	if (pwd)
		old->value = pwd->value;
	else
	{
		old->value = ft_strdup(dir);
		set_var("PWD", '=', NULL, 0);
		pwd = ret_env("PWD");
	}
	if (!getcwd(dir2, LINE_MAX))
		pwd->value = ft_strdup(pwd->value);
	else
		pwd->value = ft_strdup(dir2);
	if (flag == 1)
		pwd->value = cat_value(pwd->value, 0, "/.");
}

int		xcd(int ac, char **args, int out)
{
	int		flag;
	char	*tmp;
	char	*tmp2;
	char	dir[LINE_MAX];

	flag = 0;
	if (!ft_strcmp(args[1], ".") && !getcwd(dir, LINE_MAX) && (flag = 1))
		bi_error(args[0], "error retrieving current directory",
		strerror(errno), 0);
	if (ac > 2)
		return (bi_error(args[0], NULL, "too many arguments", 0));
	if (ac == 1 && (tmp2 = ret_envval("HOME")))
		chdir(tmp2) ? bi_error(args[0], tmp2, strerror(errno), 0) : 0;
	else if (ac == 1)
		return (bi_error(args[0], NULL, "HOME not set", 0));
	else if (!ft_strcmp(args[1], "-") && !(tmp = ret_envval("OLDPWD")))
		return (bi_error(args[0], NULL, "OLDPWD not set", 0));
	else if (!ft_strcmp(args[1], "-") && tmp && !chdir(tmp))
		ft_dprintf(out, "%s\n", tmp);
	else if (!ft_strcmp(args[1], "-") && tmp)
		return (bi_error(args[0], tmp, strerror(errno), 0));
	else if (chdir(args[1]))
		return (bi_error(args[0], args[1], strerror(errno), 0));
	set_pwdenv(dir, flag);
	return (0);
}
