/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 09:54:38 by fredrika          #+#    #+#             */
/*   Updated: 2020/02/28 13:44:36 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_fullen(char *str, int flag)
{
	if (flag == 1)
	{
		while (str != NULL && *str != '\0')
		{
			if (*str == '\n')
				return (1);
			str++;
		}
		return (0);
	}
	else
		while (str != NULL && str[flag])
			flag++;
	return (flag);
}

static char	*ft_strcat(char *file, char *buf)
{
	char	*new;
	int		i;

	if (!(new = (char *)try_malloc(ft_fullen(file, 0) + ft_fullen(
		buf, 0) + 1, _FL_)))
		return (NULL);
	i = 0;
	while (file != NULL && file[i])
	{
		new[i] = file[i];
		i++;
	}
	try_free_((void **)&file, _FL_);
	file = NULL;
	while (buf != NULL && *buf != '\0')
		new[i++] = *buf++;
	new[i] = '\0';
	return (new);
}

static char	*ft_cpyline(char **file, int i)
{
	int		j;
	char	*line;
	char	*temp;

	while (*file && (*file)[i] != '\n' && (*file)[i] != '\0')
		i++;
	if (!(line = (char *)try_malloc(i + 1, _FL_)))
		return (NULL);
	i = -1;
	while (*file && (*file)[++i] != '\n' && (*file)[i] != '\0')
		line[i] = (*file)[i];
	line[i] = '\0';
	if ((temp = NULL) == NULL && *file && (*file)[i++] != '\0')
	{
		if (!(temp = (char *)try_malloc(ft_fullen(&(*file)[i], 0) + 1, _FL_)))
			return (NULL);
		j = 0;
		while ((*file)[i] != '\0')
			temp[j++] = (*file)[i++];
		temp[j] = '\0';
	}
	try_free_((void **)file, _FL_);
	*file = temp;
	return (line);
}

int			get_next_line(int fd, char **line)
{
	char		buf[2];
	int			ret;
	static char	*file = NULL;

	if (fd < 0)
		return (-1);
	ret = -1;
	while (ft_fullen(file, 1) == 0)
	{
		if ((ret = read(fd, buf, 1)) == -1)
			return (-1);
		buf[ret] = '\0';
		file = ft_strcat(file, buf);
		if (file[0] == 0 && (file[0] = -1) < 0)
			break ;
		if (ret == 0)
			ft_dprintf(1, "  \b\b");
	}
	*line = ft_cpyline(&file, 0);
	return (ret == 0 ? 0 : 1);
}
//
// int			get_next_line(int fd, char **line)
// {
// 	char		buf[GNL_BUFFER_SIZE + 1];
// 	int			ret;
// 	static char	*file = NULL;
//
// 	if (fd < 0 || GNL_BUFFER_SIZE < 1)
// 		return (-1);
// 	ret = -1;
// 	while (ft_fullen(file, 1) == 0)
// 	{
// 		if ((ret = read(fd, buf, GNL_BUFFER_SIZE)) == -1)
// 			return (-1);
// 		buf[ret] = '\0';
// 		file = ft_strcat(file, buf);
// 		if (file[0] == 0 && (file[0] = -1) < 0)
// 			break ;
// 		if (ret == 0)
// 			ft_dprintf(1, "  \b\b");
// 	}
// 	*line = ft_cpyline(&file, 0);
// 	return (ret == 0 ? 0 : 1);
// }

// int			get_next_line(int fd, char **line)
// {
// 	// char		buf[GNL_BUFFER_SIZE + 1];
// 	char		buf[2];
// 	int			ret;
// 	static char	*file = NULL;
//
// 	if (fd < 0 || GNL_BUFFER_SIZE < 1)
// 		return (-1);
// 	ret = -1;
// 	while (ft_fullen(file, 1) == 0)
// 	{
// 		if ((ret = read(fd, buf, 1)))
// 		{
// 			buf[ret] = '\0';
// 			file = ft_strcat(file, buf);
// 		}
// 		else if (ret < 0)
// 			return (-1);
// 		else if (ret == 0 && file)
// 			ft_dprintf(1, "  \b\b");
// 		else if (ret == 0)
// 			break ;
// 	}
// 	*line = ft_cpyline(&file, 0);
// 	return (ret == 0 ? 0 : 1);
// }
