/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 09:54:38 by fredrika          #+#    #+#             */
/*   Updated: 2020/03/07 08:07:15 by tharchen         ###   ########.fr       */
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

	new = (char *)mmalloc(ft_fullen(file, 0) + ft_fullen(buf, 0) + 1);
	i = 0;
	while (file != NULL && file[i])
	{
		new[i] = file[i];
		i++;
	}
	mfree((void **)&file);
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
	line = (char *)mmalloc(i + 1);
	i = -1;
	while (*file && (*file)[++i] != '\n' && (*file)[i] != '\0')
		line[i] = (*file)[i];
	line[i] = '\0';
	if ((temp = NULL) == NULL && *file && (*file)[i++] != '\0')
	{
		temp = (char *)mmalloc(ft_fullen(&(*file)[i], 0) + 1);
		j = 0;
		while ((*file)[i] != '\0')
			temp[j++] = (*file)[i++];
		temp[j] = '\0';
	}
	mfree((void **)file);
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
		{
			ft_dprintf(1, "exit\n");
			free_all_malloc();
			exit(0);
		}
		if (ret == 0)
			ft_dprintf(1, "  \b\b");
	}
	*line = ft_cpyline(&file, 0);
	return (ret == 0 ? 0 : 1);
}
