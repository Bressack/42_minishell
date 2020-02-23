/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   git__get_current_branch_name.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 16:33:56 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/23 16:52:43 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define CURR_DIR	"/Users/tharchen/Prog/42/circle_4/minishell"

char		*git__get_current_branch_name(char **env)
{
	pid_t	pid;
	char	*av[];
	char	*git_dir;

	git_dir = ft_strjoin(3, CURR_DIR, "/", ".git")
	if (opendir())
	if ((pid = fork()))
		execve("git", env);
}
