/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 17:17:28 by tharchen          #+#    #+#             */
/*   Updated: 2020/01/27 17:36:38 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ms.h>
#include <libc.h>
#include <stdlib.h>
#include <get_next_line.h>

t_cmd				*g_exp = NULL;
t_cmd				*g_last_cmd = NULL;
t_cmd				*g_last_arg = NULL;
int					g_needling = ISCMD;
/*

ls -lRah | cat -e | grep "xds i ui iu 'n un9' uno p" && rm -rf / ; ls -l && echo  -n "ok les potos" > test || > test2 echo -n "lel op" > test3

ls -lRah | cat -e | grep "xds i ui iu 'n un9' uno p"
                                                        rm -rf /
								                                   ls -l
								                      			            echo  -n "ok les potos" > test
								                      					                                      > test2 echo -n "lel op" > test3

*/

void				new_element(char *data, int type, ...)
{
	va_list	*ap;

	va_start(ap, type);
	if (type == ISARG)
		add_new_arg(data, ap);
	else if (type == ISCMD)
		add_new_cmd(data, ap);
}

void				print_prompt(int select)
{
	char			*color_arrow;

	if (select == PROMPT_NORMAL)
	{
		color_arrow = g_all->ret_last_cmd == SUCCESS ? C_G_GREEN : C_G_RED;
		printf("%s%s"C_G_CYAN" %s"C_RES" \n",
			color_arrow, PROMPT_ARROW, g_all->curr_dir);
	}
	else if (select == PROMPT_NEXT_NEEDED)
		printf("> ");
}

int					pass_space(char *line, int *i)
{
	int				nb;

	nb = 0;
	while (ft_isspace(line[*i]) && ++nb)
		(*i)++;
	return (nb);
}

void				parser__quote(char *line, int *i, int *j)
{
	(*j) = (*i) + 1;
	while (1)
	{
		if (line[(*j)] == '\\')
			(*j)++;
		if (line[(*j)] == '\0')
		{
			new_element(
				ft_strndup(&line[(*i)], (*j) - (*i)), g_needling, ISQUOTE, QUOTE_OPEN);
			preparser(PROMPT_NEXT_NEEDED);
			return ;
		}
		else if (line[(*j) - 1] != '\\' && line[(*j)] == kotte)
			break ;
		(*j)++;
	}
	new_element(
		ft_strndup(&line[(*i)], (*j) - (*i)), g_needling, ISQUOTE, QUOTE_CLOSE);
	pass_space(line, i);
}

void				ft_isvalid_char(char c)
{
	if ()
}

void				parser__valid_char(char *line, int *i, int *j)
{
	(*j) = (*i) + 1;
	while (ft_isvalid_char(line[(*j)])) // ft_isvalid_char TODO
		(*j)++;
	new_element(
		ft_strndup(&line[i], (*j) - (*i)), g_needling, ISNOTQUOTE, QUOTE_CLOSE);
	g_needling = ISARG;
	pass_space(line, i);
}

int					ft_isspecial(char *s)
{
	return ((*s == ';') || (*s == '&' && *(s + 1) == '&') || (*s == '&') ||
		(*s == '|' && *(s + 1) == '|') || (*s == '|') ? 1 : 0);
}

void				parser__link__colon(void)
{
	g_last_cmd->link = LINK_COLON_;
	g_needling = ISCMD;
}

void				parser__link__dbland(void) // BONUS
{
	g_last_cmd->link = LINK_AND___;
	g_needling = ISCMD;
}

void				parser__link__and(void) // BONUS
{
	g_last_cmd->link = LINK_THREAD;
	g_needling = ISCMD;
}

void				parser__link__dblor(void) // BONUS
{
	g_last_cmd->link = LINK_OR____;
	g_needling = ISCMD;
}

void				parser__link__pipe(void)
{
	g_last_cmd->link = LINK_PIPE__;
	g_needling = ISCMD;
}

void				parser__link__dblrafters_right(void)
{
	g_last_cmd->link = REDIR_DBLRIGHT;
	g_needling = ISARG;
}

void				parser__link__dblrafters_left(void) // BONUS
{
	g_last_cmd->link = REDIR_DBLLEFT_;
	g_needling = ISARG;
}

void				parser__link__rafters_right(void)
{
	g_last_cmd->link = REDIR_RIGHT___;
	g_needling = ISARG;
}

void				parser__link__rafters_left(void)
{
	g_last_cmd->link = REDIR_LEFT____;
	g_needling = ISARG;
}

void				parser__link(char *line, int *i, int *j)
{
	if (line[*i] == ';')
		parser__link__colon();
	else if (line[*i] == '&' && line[*i + 1] == '&')	// BONUS
		parser__link__dbland();
	else if (line[*i] == '&')							// BONUS
		parser__link__and();
	else if (line[*i] == '|' && line[*i + 1] == '|')	// BONUS
		parser__link__dblor();
	else if (line[*i] == '|')
		parser__link__pipe();
	else if (line[*i] == '>' && line[*i + 1] == '>')
		parser__link__dblrafters_right();
	else if (line[*i] == '<' && line[*i + 1] == '<')	// BONUS
		parser__link__dblrafters_left();
	else if (line[*i] == '>')
		parser__link__rafters_right();
	else if (line[*i] == '<')
		parser__link__rafters_left();
}

void				parser(char *line)
{
	int				i;
	int				j;
	char			kotte;
	char			bslsh;

	i = 0;
	bslsh = 0;
	while (1)
	{
		pass_space(line, &i);
		if (!line[i])
			break ;
		if (line[i] == '\\' && (bslsh = 1))
			i++;
		if (!bslsh && (line[i] == '\"' || line[i] == '\'') && (kotte = line[i]))
			parser__quote(&g_exp, line, &i, &j);
		else if (!bslsh && ft_isspecial(line[i]))
			parser__link(line[i], i);
		else if (bslsh || ft_isvalid_char(line[i])) // ft_isvalid_char TODO
			parser__valid_char(&g_exp, line, &i, &j);
		else
			return (error(i, line, "invalid symbole"));
		i = j;
		bslsh = 0;
	}
}

void				add_new_arg(char *data, va_list ap)
{
	t_cmd			*tmp_c;
	t_arg			*tmp_a;
	t_pnp			*new;
	int				quote[2];

	new = try_malloc(sizeof(t_arg), _FL_);
	quote[0] = va_arg(ap, int);
	quote[1] = va_arg(ap, int);
	new->data = data;
	new->quote &= quote[0];
	new->quote &= quote[1];
	tmp_c = g_exp;
	while (tmp_c->next);
		tmp_c = tmp_c->next;
	ft_add_node_end_np((t_pnp **)(&tmp_c->av), new);
	g_last_arg = (t_arg *)new;
}

void				add_new_cmd(char *data, va_list ap)
{
	t_pnp			*new;

	new = try_malloc(sizeof(t_cmd), _FL_);
	new->fd_in = FD_STDIN;
	new->fd_out = FD_STDOUT;
	ft_add_node_end_np(&g_exp, new);
	g_last_cmd = (t_cmd *)new;
}

void				preparser(int prompt)
{
	char			*line;

	line = NULL;
	print_prompt(prompt);
	get_next_line(0, &line);
	if (line && ft_strlen(line))
		parser(line);
	try_free_(line, _FL_);
}

void				init(void)
{
	g_exp = try_malloc(sizeof(t_cmd), _FL_);
}

void				__f__ft_del_node_np__t_cmd__(t_pnp *a)
{
	t_cmd			*tmp;

	tmp = (t_cmd *)a
	try_free_(tmp->name);
	ft_del_list_np(&tmp->av, __f__ft_del_node_np__t_arg__);
}

void				__f__ft_del_node_np__t_arg__(t_pnp *a)
{
	t_arg			*tmp;

	tmp = (t_arg *)a
	try_free_(tmp->data);
}

void				reset_exp(void)
{
	ft_del_list_np(&g_exp, __f__ft_del_node_np__t_arg__);
}

int					main(void)
{
	init();
	while (1)
	{
		reset_exp(); // DONE // works ? TO TEST // norme OK !
		preparser(PROMPT_NORMAL); // IN PROGRESS
		process(); // TODO
	}
	return (0);
}



