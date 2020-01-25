/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 17:17:28 by tharchen          #+#    #+#             */
/*   Updated: 2020/01/21 04:53:28 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ms.h>
#include <libc.h>
#include <stdlib.h>
#include <get_next_line.h>

t_sep			g_cmd_sep[3] =
{
	{"|"},
	{"&&"},
	{"||"}
};

t_sep			g_exp_sep[5] =
{
	{";"},
	{"&"},
	{"&|"},
	{"&!"},
	{NULL}
};

/*
"ls ; ls | ls && ls ; ls || ls"

 ls
      ls | ls && ls
	                  ls || ls


t_exp{ t_cmd{ls} }->t_exp{ t_cmd{ls}->t_sep{"|"}->t_cmd{ls}->t_sep{"&&"}->t_cmd{ls} }->t_exp{ t_cmd{ls}->t_sep{"||"}->t_cmd{ls} }->NULL
*/


int					main(void)
{
	char	*line;
	char	**split;
	int		pid;

	while (dprintf(1, "prompt>: ") && get_next_line(0, &line))
	{
		if (line && strlen(line))
		{
			split = ft_strsplit_array(line, ' ');
			char *tmp;
			tmp = ft_strjoin(2, "/bin/", split[0]);
			if ((pid = fork()))
			{
				if (execve(tmp, &split[0], NULL) == -1)
				{
					dprintf(2, "42sh: error command: %s\n", tmp);
					exit(1);
				}
			}
			wait(NULL);
			free(tmp);
			dprintf(1, "process successed\n");
		}
	}
	return (0);
}
