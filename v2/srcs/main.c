/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:44:55 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/06 16:45:57 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ms.h>

void	ft_error(int type, int idx)
{
	if (type == ERR)
	{
		if (idx == GNL__BADREAD)
			dprintf(2, ""C_G_RED"fatal error: "C_G_WHITE"unable to read the standard input (stdin)"C_RES"\n");
	}
}

void	__f__ft_del_list_np___t_lex(t_pnp *curr)
{
	try_free_((void **)(&((t_lex *)curr)->str), _FL_);
}

int		main(void)
{
	char	*line;
	t_lex	*lex;

	while (1)
	{
		lex = NULL;
		dprintf(1, "minishell-0.1$ ");
		if (get_next_line(0, &line) == -1)
			ft_error(ERR, GNL__BADREAD);
		lex = lexer(line);
		try_free_((void **)&line, _FL_);
		for (t_lex *tmp = lex ; tmp ; tmp = tmp->next)
			printf("token [ not defined ] : {%s}\n", tmp->str);
		ft_del_list_np((t_pnp **)lex, __f__ft_del_list_np___t_lex);
		print_mem__(PRINT_ALL);
	}
	return (0);
}
