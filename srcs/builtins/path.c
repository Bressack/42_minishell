/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 18:37:56 by frlindh           #+#    #+#             */
/*   Updated: 2020/03/02 20:21:57 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_next_path(char **env, char *command)
{
	int		i;
	char	*path;

	i = 0;
	while ((*env)[i] && (*env)[i] != '\n' && (*env)[i] != ':')
		i++;
	path = (char *)mmalloc(sizeof(char) * (i + ft_strlen(command) + 1));
	i = 0;
	while (**env && **env != '\n' && **env != ':')
		path[i++] = *((*env)++);
	if (**env == ':')
		(*env)++;
	path[i++] = '/';
	while (command && *command)
		path[i++] = *command++;
	path[i] = '\0';
	return (path);
}

char	*get_no_path(char *com)
{
	int		i;
	char	*path;

	path = (char *)mmalloc(sizeof(char) * (ft_strlen(com)) + 3);
	i = 0;
	path[i++] = '.';
	path[i++] = '/';
	while (com && *com)
		path[i++] = *com++;
	path[i] = '\0';
	return (path);
}

char	*get_path(char *command)
{
	int			i;
	char		*env;
	char		*path;
	struct stat	buf;

	i = -1;
	path = NULL;
	while (command[++i] && (command[i] == '.' || command[i] == '/'))
		if (command[i] == '/' && (i = -1) < 0)
			break ;
	if (i == -1)
		path = command;
	else if (!ret_envval("PATH"))
		path = get_no_path(command);
	else
		env = ret_envval("PATH");
	if (path)
		return (!stat(path, &buf)) ? (path) : (NULL);
	while (env && *env && (path = get_next_path(&env, command)))
	{
		if (!stat(path, &buf))
			return (path);
		mfree(path);
	}
	return (NULL);
}
