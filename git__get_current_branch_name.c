/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   git__get_current_branch_name.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 16:33:56 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/27 00:39:23 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <libc.h>
// # define CURR_DIR	"/Users/tharchen/Prog/42/circle_4/minishell"
# define CURR_DIR	"/Users/user/Prog/42/projects/circle_4/minishell"

static void	*join(char **ret, char *arg, int *retsize)
{
	char	*tmp;
	int		size;

	size = strlen(arg);
	if (!(tmp = malloc(sizeof(char) * (*retsize + size + 1))))
		return (NULL);
	memcpy(tmp, *ret, *retsize);
	memcpy(tmp + *retsize, arg, size);
	*retsize += size;
	tmp[*retsize] = '\0';
	free(*ret);
	*ret = tmp;
	return (tmp);
}

char		*ft_strjoin(int nb_str, ...)
{
	char	*arg;
	char	*ret;
	va_list	ap;
	int		size;

	ret = NULL;
	size = 0;
	va_start(ap, nb_str);
	while (nb_str--)
	{
		if (!(arg = va_arg(ap, char *)))
			continue ;
		if (!ret)
		{
			if (!(ret = strdup(arg)))
				return (NULL);
			size = strlen(ret);
		}
		else
			if (join(&ret, arg, &size) == NULL)
				return (NULL);
	}
	va_end(ap);
	return (ret);
}


char		*git__get_current_branch_name(char **env)
{
	pid_t	pid;
	char	**av;
	int		stt;

	int		fd[2];

	if (pipe(fd) != 0)
		return (NULL);
	av = malloc(sizeof(char *) * 3);
	av[0] = strdup("/bin/cat");
	av[1] = ft_strjoin(3, CURR_DIR, "/", ".git/HEAD");
	av[2] = NULL;
	if (!(pid = fork()))
	{
		close(0);
		fd[1] = dup(0);
		dprintf(fd[1], "CACA\n");
		execve("/bin/cat", av, env);
		exit(-1);
	}
	waitpid(pid, &stt, WUNTRACED);
	printf("$?: %d\n", stt);
	free(av[0]);
	free(av[1]);
	free(av);

	char	buf[1024 + 1];
	int		ret;

	ret = read(fd[0], buf, 1024);
	buf[ret] = 0;

	printf("read: [%s]\n", buf);
	return (NULL);
}

int		main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	git__get_current_branch_name(env);
	return (0);
}

