/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:16:47 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/06 12:44:55 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void			ft_putchar(char c)
{
	write(1, &c, 1);
}

static void			ft_putstr(char *s)
{
	write(1, s, strlen(s));
}

static void			ft_putendl(char *s)
{
	ft_putstr(s);
	write(1, "\n", 1);
}

static void			print_lexed(t_lexer *lexed)
{
	t_list			*drive;

	if (lexed == NULL)
		ft_putstr("Malloc error or empty str\n\n");
	else
	{
		ft_putstr("lexed error\t\t");
		if (lexed->err == 0)
			ft_putendl("None");
		else if (lexed->err == InLexError)
			ft_putendl("Lexical Error");
		else if (lexed->err == InSynError)
			ft_putendl("Syntax Error");
		ft_putstr("lexed error_type\t");
		if (lexed->err_type == None)
			ft_putendl("None");
		else if (lexed->err_type == Escapment)
			ft_putendl("Escapment");
		else if (lexed->err_type == Frame)
			ft_putendl("Frame");
		else if (lexed->err_type == Identifier)
			ft_putendl("Identifier");
		else if (lexed->err_type == Separator)
			ft_putendl("Separator");
		else if (lexed->err_type == Redirector)
			ft_putendl("Redirector");
		ft_putstr("lexed error_index\t");
		ft_putnbr(lexed->err_index);
		ft_putstr("\n\n");
		drive = lexed->tokenlst;
		while (drive != NULL)
		{
			if (((t_token *)(drive->content))->type == None)
				ft_putstr("None");
			else if (((t_token *)(drive->content))->type == Escapment)
				ft_putstr("Escapment");
			else if (((t_token *)(drive->content))->type == Frame)
				ft_putstr("Frame\t");
			else if (((t_token *)(drive->content))->type == Identifier)
				ft_putstr("Identifier");
			else if (((t_token *)(drive->content))->type == Separator)
				ft_putstr("Separator");
			else if (((t_token *)(drive->content))->type == Redirector)
				ft_putstr("Redirector");
			ft_putstr("\t\t[");
			ft_putstr(((t_token *)(drive->content))->value);
			ft_putendl("]");
			drive = drive->next;
		}
		ft_putchar('\n');
	}
	ft_putendl("---------------------------------------------------------\n");
}

int			main(int ac, char **av)
{
	t_lexer	*lexed;
	int		i;

	if (ac < 2)
		write(1, "Too few argument\n", 17);
	else
	{
		i = 1;
		while (i < ac)
		{
			lexed = str_lex(av[i++]);
			print_lexed(lexed);
			if (lexed)
				destroy_lexed(&lexed);
		}
	}
	return (0);
}
