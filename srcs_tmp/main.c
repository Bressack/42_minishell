/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 17:17:28 by tharchen          #+#    #+#             */
/*   Updated: 2020/01/19 17:40:14 by tharchen         ###   ########.fr       */
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

t_exp				*parser(char *str)
{
	char			**split_exp;

	split_exp = ft_strsplit_array(str, g_exp_sep[0]/* ";" */);
	i = 0;
	while (split_exp[i])
	{

	}
}

void				print_prompt(void)
{
	char			*color_arrow;

	color_arrow = g_all->ret_last_cmd == SUCCESS ? C_G_GREEN : C_G_RED;
	printf("%s%s"C_G_CYAN" %s"C_RES" \n", color_arrow, PROMPT_ARROW, g_all->curr_dir);
}

int					main(void)
{
	char	*line;
	char	**split;
	int		pid;

	print_prompt();
	while (dprintf(1, "prompt>: ") && get_next_line(0, &line))
	{
		if (line && strlen(line))
		{
			if (pid = fork())
			{
				split = ft_strsplit(line, ' ');
				char *tmp;
				tmp = ft_strjoin("/bin/", split[0]);
				if (execve(tmp, &split[0], NULL) == -1)
				{
					dprintf(2, "42sh: error command: %s\n", tmp);
					exit(1);
				}
				free(tmp);
				dprintf(1, "process successed\n");
				exit(0);
			}
			waitpid(pid);
			// dprintf(1, "42sh: command not found: %s\n", line);
		}
	}
	return (0);
}
