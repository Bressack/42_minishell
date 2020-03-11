/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 09:54:38 by fredrika          #+#    #+#             */
/*   Updated: 2020/03/11 21:19:27 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_next_line(void)
{
	char	*buf;
	int		ret;
	int		position;
	char	red[2];

	position = 0;
	buf = (char *)mmalloc(4096);
	while (1)
	{
		ret = read(0, red, 1);
		if (g_reset == 1 && !(g_reset = 0))
			position = 0;
		if (ret == 0 && position == 0)
		{
			dprintf(2, "exit\n");
			free_all_malloc();
			exit (0);
		}
		if ((red[0] == '\n' || position >= 4095) && !(buf[position] = '\0'))
			return (buf);
		else if (ret)
			buf[position++] = red[0];
	}
}
