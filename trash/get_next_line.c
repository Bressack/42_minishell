/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 08:56:08 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/17 12:17:32 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int		gnl_u(char *s1, char **s2, char *s3, int cc)
{
	int			i;

	i = -1;
	if (!s2 && !s3 && cc == -1)
	{
		while (s1 && s1[++i])
			if (s1[i] == '\n')
				return (i);
		return (-1);
	}
	else if (!s3 && cc == -1)
	{
		while (s1 && s1[++i])
			;
		return (i == -1 ? 0 : i);
	}
	if (cc)
		while (cc == -1 ? s3[++i] : ++i < cc)
			s1[i] = s3[i];
	s1[i == -1 ? 0 : i] = 0;
	s2 ? *s2 = s1 : 0;
	return (0);
}

static int		fill_save(int *fd, char **save)
{
	char		buf[GNL_BUFFER_SIZE + 1];
	char		*tmp;
	int			len[2];

	len[GNL_LEN] = 0;
	len[GNL_RET] = 0;
	while (1)
	{
		if (gnl_u(*save, NULL, NULL, -1) != -1)
			return (gnl_u(*save, NULL, NULL, -1));
		len[GNL_LEN] = gnl_u(*save, (char **)1, NULL, -1);
		if ((len[GNL_RET] = read(*fd, buf, GNL_BUFFER_SIZE)) < 0)
			return (-1);
		if (!len[GNL_RET] && (*fd = -1))
			return (len[GNL_LEN]);
		buf[len[GNL_RET]] = 0;
		tmp = try_malloc((len[GNL_RET] + len[GNL_LEN] + 1), NULL, 0);
		gnl_u(tmp, NULL, *save, len[GNL_LEN]);
		gnl_u(tmp + len[GNL_LEN], NULL, buf, len[GNL_RET]);
		try_free_((void **)save, NULL, 0);
		*save = tmp;
	}
}

int				get_next_line(int fd, char **line)
{
	static char	*save = NULL;
	char		*tmp[2];
	size_t		pos_nl;

	if (fd < 0 || !line || (pos_nl = fill_save(&fd, &save)) == -1)
	{
		try_free_((void **)&save, NULL, 0);
		return (-1);
	}
	*line = try_malloc(pos_nl + 1, NULL, 0);
	if (!save)
		return (0);
	gnl_u(*line, NULL, save, pos_nl);
	if (gnl_u(save, (char **)1, NULL, -1) - pos_nl)
	{
		tmp[0] = try_malloc(gnl_u(save,
			(char **)1, NULL, -1) - pos_nl + 1, NULL, 0);
		gnl_u(tmp[0], &tmp[1], save + pos_nl + 1, -1);
		try_free_((void **)&save, NULL, 0);
		save = tmp[1];
	}
	if (fd == -1)
		try_free_((void **)&save, NULL, 0);
	return (fd == -1 ? 0 : 1);
}
