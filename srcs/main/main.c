/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 17:17:28 by tharchen          #+#    #+#             */
/*   Updated: 2020/01/30 17:43:09 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ms.h>
#include <libc.h>
#include <stdlib.h>
#include <get_next_line.h>

t_env				*g_env = NULL;
t_cmd				*g_exp = NULL;
t_cmd				*g_last_cmd = NULL;
t_arg				*g_last_arg = NULL;
int					g_needling = ISCMD;
char				*g_line = NULL;
t_arg				*g_av_in = NULL;
t_arg				*g_av_out = NULL;
t_arg				*g_av = NULL;
int					g_ret_last_cmd = SUCCESS;
char				*g_curr_dir;

void				print_prompt(int select)
{
	char			*color_arrow;

	if (select == PROMPT_NORMAL)
	{
		color_arrow = g_ret_last_cmd == SUCCESS ? C_G_GREEN : C_G_RED;
		dprintf(1, "%s%s"C_G_CYAN"  %s"C_RES" ",
			color_arrow, PROMPT_ARROW, g_curr_dir);
	}
	else if (select == PROMPT_NEXT_NEEDED)
		dprintf(1, "> ");
}

void				cmd_stop(int type)
{
	g_needling = type;
	g_av_out = NULL;
	g_av_in = NULL;
	g_av = NULL;
}

void				reset_exp(void)
{
	debug_print_msg("reset g_exp", _FL_);
	ft_del_list_np((t_pnp **)&g_exp, __f__ft_del_node_np__t_cmd__);
	// print_mem__(PRINT_OK);
	g_exp = NULL;
}

void				init_env(char **env)
{
	t_env			*new;
	int				i;
	int				j;

	i = -1;
	while (env[++i])
	{
		new = try_malloc(sizeof(t_env), _FL_);
		if ((j = ft_strfind(env[i], '=')) == -1)
			exit(-1); // error(); // TODO // value is missing in env element
		new->key = ft_substr(env[i], 0, j);
		new->value = ft_substr(env[i], j + 1, ft_strlen(env[i]));
		ft_add_node_end_np((t_pnp **)&g_env, (t_pnp *)new);
	}
}

int					main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	printf(" --- minishell v0.0.1 ---\n");
	debug_print_msg("start", _FL_);
	init_env(env);
	for (t_env *tmp = g_env ; tmp ; tmp = tmp->next)
	{
		// printf(""C_G_CYAN"key"C_RES": %s | "C_G_CYAN"value"C_RES": %s\n", tmp->key, tmp->value);
		printf(""C_G_CYAN"%s"C_RES"="C_G_MAGENTA"%s"C_RES"\n", tmp->key, tmp->value);
	}

	while (1)
	{
		preparser(PROMPT_NORMAL); // IN PROGRESS
		parser();
		debug__print_data();
		// process(); // TODO
		reset_exp(); // DONE // works ? TO TEST // norme OK !
		debug__print_data();
	}
	debug_print_msg("end", _FL_);
	return (0);
}
