/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 17:17:28 by tharchen          #+#    #+#             */
/*   Updated: 2020/01/24 19:01:12 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ms.h>
#include <libc.h>
#include <stdlib.h>
#include <get_next_line.h>

t_sep			g_cmd_sep[1] =
{
	{"|"},
};

t_sep			g_exp_sep[3] =
{
	{";"},
	{"&&"},
	{"||"},
	{NULL}
};

/*

ls -lRah | cat -e | grep "xds i ui iu 'n un9' uno p" && rm -rf / ; ls -l && echo  -n "ok les potos" > test || > test2 echo -n "lel op" > test3

ls -lRah | cat -e | grep "xds i ui iu 'n un9' uno p"
                                                        rm -rf /
								                                   ls -l
								                      			            echo  -n "ok les potos" > test
								                      					                                      > test2 echo -n "lel op" > test3

*/

# define LINK_SEMICON	0
# define LINK_PIPE___	1
# define LINK_AND____	2
# define LINK_OR_____	3

typedef struct		s_arg
{
	struct s_arg	*next;
	struct s_arg	*prev;
	char			*data;
}					t_arg;
typedef struct		s_cmd
{
	struct s_cmd	*next;
	struct s_cmd	*prev;
	char			*name;
	t_arg			*av;
	int				fd_out;
	int				fd_in;
	int				link;
}					t_cmd;

t_exp				*parser(char *str)
{
	int				start;
	int				end;

	start = 0;
	while (1)
	{
		if (ft_isspace(str[start]))
			while (ft_isspace(str[start]))
				start++;
		else if (ft_isalnum(str[start]))
		{

		}

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


!\"#$%&\'()*+,-.\/0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_\`abcdefghijklmnopqrstuvwxyz{|}~
