/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   git__get_current_branch_name.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 16:33:56 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/23 20:15:25 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <libc.h>
# define CURR_DIR	"/Users/tharchen/Prog/42/circle_4/minishell"

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


char		*git__get_current_branch_name(char **av, char **env)
{
	pid_t	pid;
	char	**avv;
	int		stt;

	avv = malloc(sizeof(char *) * 3);
	avv[0] = strdup("/bin/cat");
	avv[1] = ft_strjoin(3, CURR_DIR, "/", ".git/HEAD");
	avv[2] = NULL;
	if (!(pid = fork()))
	{
		execve("/bin/cat", avv, env);
		exit(-1);
	}
	waitpid(pid, &stt, WUNTRACED);
	printf("$?: %d\n", stt);
	free(avv[0]);
	free(avv[1]);
	free(avv);
	return (NULL);
}

int		main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	git__get_current_branch_name(av, env);
	return (0);
}

