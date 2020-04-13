/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 18:37:56 by frlindh           #+#    #+#             */
/*   Updated: 2020/04/13 14:00:09 by tharchen         ###   ########.fr       */
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

int		file_name_too_long(char *path)
{
	int			i;
	int			last;
	int			length;

	i = -1;
	last = 0;
	length = 0;
	while (path && path[++i])
	{
		if (path[i] == '/')
			last = i;
		if (i - last > length)
			length = i - last;
	}
	return (length > 255 || i > 1024);
}

int		check_stat(char *path, int *err, int f)
{
	int			ret;
	struct stat	buf;

	ret = stat(path, &buf);
	if (file_name_too_long(path))
		*err = 124;
	else if (ret < 0)
		*err = 127 + f;
	else if (!(buf.st_mode & S_IXUSR))
		*err = 126;
	else if (S_ISDIR(buf.st_mode))
		*err = 125;
	else if (!(*err = 0))
		return (1);
	return (0);
}

/*
** WILL EITHER RETURN
** 1. THE COMMAND IF A FULL PATH MEANING FOR EX [./test] [../test] [/bin/ls]
** 2. ADD A ./ TO THE COMMAND AND SEARCH CURRENT DIR IF PATH IS UNSET
** 3. WILL SEARCH IN ALL DIR DEFINES BY PATH TO SEE IF EXECUTABLE IS THERE
** 4. NULL IF NOT FOUND
*/

char	*get_path(char *command, int *err)
{
	int			i;
	char		*env;
	char		*path;

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
		return (check_stat(path, err, 0)) ? (path) : (NULL);
	while (env && *env && (path = get_next_path(&env, command)))
	{
		if (check_stat(path, err, 1))
			return (path);
		mfree((void **)&path);
	}
	return (NULL);
}
