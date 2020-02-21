/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 09:54:38 by fredrika          #+#    #+#             */
/*   Updated: 2020/02/20 22:25:35 by fredrikalindh    ###   ########.fr       */
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

	if (!(new = (char *)malloc(ft_fullen(file, 0) + ft_fullen(buf, 0) + 1)))
		return (NULL);
	i = 0;
	while (file != NULL && file[i])
	{
		new[i] = file[i];
		i++;
	}
	free(file);
	file = NULL;
	while (buf != NULL && *buf != '\0')
		new[i++] = *buf++;
	new[i] = '\0';
	return (new);
}

static char	*ft_cpyline(char *file, int i)
{
	int		j;
	char	*line;
	char	*temp;

	while (file && file[i] != '\n' && file[i] != '\0')
		i++;
	if (!(line = (char *)malloc(i + 1)))
		return (NULL);
	i = -1;
	while (file && file[++i] != '\n' && file[i] != '\0')
		line[i] = file[i];
	line[i] = '\0';
	if ((temp = NULL) == NULL && file && file[i++] != '\0')
	{
		if (!(temp = (char *)malloc(ft_fullen(&file[i], 0) + 1)))
			return (NULL);
		j = 0;
		while (file[i] != '\0')
			temp[j++] = file[i++];
		temp[j] = '\0';
	}
	free(file);
	file = temp;
	return (line);
}

int			get_next_line(int fd, t_lexer *l)
{
	char		buf[GNL_BUFFER_SIZE + 1];
	int			ret;
	char		*file;

	file = NULL;
	if (fd < 0 || GNL_BUFFER_SIZE < 1)
		return (-1);
	ret = -1;
	while (ft_fullen(file, 1) == 0 && ret != 0)
	{
		if ((ret = read(fd, buf, GNL_BUFFER_SIZE)) == -1)
			return (-1);
		buf[ret] = '\0';
		file = ft_strcat(file, buf);
	}
	l->line = ft_cpyline(file, 0);
	l->len_line = ft_strlen(l->line);
	l->pos = 0;
	l->current_char = l->line[l->pos];
	return (ret == 0 ? 0 : 1);
}
