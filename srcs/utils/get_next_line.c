/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 09:54:38 by fredrika          #+#    #+#             */
/*   Updated: 2020/03/24 13:49:36 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_next_line(void)
{
	char	*buf;
	int		ret;
	int		pos;
	char	red[2];

	pos = 0;
	buf = (char *)mmalloc(4096);
	while (1)
	{
		if ((ret = read(0, red, 1)) == -1)
			return (NULL);
		if (g_reset == 1 && !(g_reset = 0))
			pos = 0;
		if (ret == 0 && pos == 0 && ft_dprintf(2, "  \b\bexit\n"))
		{
			free_all_malloc();
			exit(g_exit);
		}
		if (!ret)
			ft_dprintf(2, "  \b\b");
		else if ((red[0] == '\n' || pos >= 4095) && !(buf[pos] = '\0'))
			return (buf);
		else
			buf[pos++] = red[0];
	}
}
