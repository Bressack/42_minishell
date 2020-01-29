/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 17:17:28 by tharchen          #+#    #+#             */
/*   Updated: 2020/01/29 21:12:53 by tharchen         ###   ########.fr       */
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
char				*g_line;
t_arg				*g_av_in;
t_arg				*g_av_out;
t_arg				*g_av;

void				__f__ft_del_node_np__t_cmd__(t_pnp *a)
{
	try_free_((t_arg *)a->name);
	ft_del_list_np(&((t_arg *)a->av), __f__ft_del_node_np__t_arg__);
}

void				__f__ft_del_node_np__t_arg__(t_pnp *a)
{
	try_free_((t_arg *)a->data);
}

				//  new_element(data, ISARG     , QUOTE_OPEN || QUOTE_CLOSE);
				//  new_element(data, ISARG_IN  , QUOTE_OPEN || QUOTE_CLOSE);
				//  new_element(data, ISARG_OUT , QUOTE_OPEN || QUOTE_CLOSE);
				//  new_element(data, ISCMD     , QUOTE_OPEN || QUOTE_CLOSE);
void				new_element(char *data, int type, ...)
{
	va_list	*ap;

	va_start(ap, type);
	if (type == ISARG)
		add_new_arg(data, ISARG, ap);
	else if (type == ISARG_IN)
		add_new_arg(data, ISARG_IN, ap);
	else if (type == ISARG_OUT)
		add_new_arg(data, ISARG_OUT, ap);
	else if (type == ISCMD)
		add_new_cmd(data, ap);
}

int					ft_isquote(char c)
{
	return (c == '\"' || c == '\'');
}

#if BONUS == ON // ft_isspecial bonus

int					ft_isspecial(char *s)
{
	return ((*s == ';') ||                     // ;
			(*s == '&' && *(s + 1) == '&') ||  // &&
			(*s == '|' && *(s + 1) == '|') ||  // ||
			(*s == '|') ||                     // |
			(*s == '&'));                      // &

}
#else // ft_isspecial mandatory part
int					ft_isspecial(char *s)
{
	return ((*s == ';') ||                     // ;
			(*s == '|'));                      // |
}
#endif

int					pass_quotes(int *i, int *j)
{
	while (g_line[*j] && ft_isquote(g_line[*j]))
		(*j)++;
	return (!g_line[*j] ? QUOTE_OPEN : QUOTE_CLOSE);
}

void				add_new_arg(char *data, int type, va_list ap)
{
	t_pnp			*new;
	int				quote[2];

	new = try_malloc(sizeof(t_arg), _FL_);
	quote[0] = va_arg(ap, int);
	quote[1] = va_arg(ap, int);
	new->data = data;
	new->quote &= quote[0];
	new->quote &= quote[1];
	if (type == ISARG_IN)
	{
		ft_add_node_end_np((t_pnp **)(&g_av_in), new);
		!new ? g_last_cmd->av_in = new : 0;
	}
	else if (type == ISARG_OUT)
	{
		ft_add_node_end_np((t_pnp **)(&g_av_out), new);
		!new ? g_last_cmd->av_out = new : 0;
	}
	else
	{
		ft_add_node_end_np((t_pnp **)(&g_av), new);
		!new ? g_last_cmd->av = new : 0;
	}
	g_last_arg = (t_arg *)new; // IDKIIIU
}

void				add_new_cmd(char *data, va_list ap)
{
	t_pnp			*new;

	new = try_malloc(sizeof(t_cmd), _FL_);
	new->fd_in = FD_STDIN;
	new->fd_out = FD_STDOUT;
	new->av_in = g_av_in;
	new->av_out = g_av_out;
	new->av = g_av;
	ft_add_node_end_np(&g_exp, new);
	g_last_cmd = (t_cmd *)new;
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

int					pass_space(int *i)
{
	int				nb;

	nb = 0;
	while (ft_isspace(g_line[*i]) && ++nb)
		(*i)++;
	return (nb);
}

void				parser__quote(int *i, int *j)
{
	(*j) = (*i) + 1;
	while (1)
	{
		if (g_line[(*j)] == '\0')
			break ;
		if (g_line[(*j) - 1] != '\\' && g_line[(*j)] == )
			break ;
		if (g_line[(*j)] == '\\')
			(*j) += 2;
		else
			(*j)++;
	}
	new_element(
		ft_strndup(&g_line[(*i)], (*j) - (*i)), g_needling, ISQUOTE, !g_line[(*j)] ? QUOTE_OPEN);
	pass_space(g_line, i);
}

void				parser__valid_char(int *i, int *j)
{
	(*j) = (*i) + 1;
	while (!ft_isspecial(g_line[(*j)]) && !ft_isspace(g_line[(*j)]))
	{
		if (ft_isquote(g_line[(*j)]) && pass_quotes(g_line, i, j) == QUOTE_OPEN)
		{
			preparser(PROMPT_NEXT_NEEDED);
			break ;
		}
		else
			(*j)++;
	}

	new_element(
		ft_strndup(&g_line[i], (*j) - (*i)), g_needling, ISNOTQUOTE, QUOTE_CLOSE);
	g_needling = ISARG;
	pass_space(g_line, i);
}

// return ((*s == ';') || (*s == '&' && *(s + 1) == '&') || (*s == '&') ||
// 	(*s == '|' && *(s + 1) == '|') || (*s == '|') ? 1 : 0);

void				cmd_stop(int type)
{
	g_needling = type;
	g_av_in = NULL;
	g_av_out = NULL;
	g_av = NULL;
}

#ifdef BONUS

void				parser__link__dbland(void) // ------------------------------: &&	BONUS
{
	g_last_cmd->link = LINK_AND___;
	cmd_stop(ISCMD);
	g_needling = ISCMD;
}

void				parser__link__and(void) // ---------------------------------: &		BONUS
{
	g_last_cmd->link = LINK_THREAD;
	g_needling = ISCMD;
}

void				parser__link__dblor(void) // -------------------------------: ||	BONUS
{
	g_last_cmd->link = LINK_OR____;
	g_needling = ISCMD;
}

void				parser__link__dblrafters_left(void) // ---------------------: <<	BONUS
{
	g_last_cmd->link = REDIR_DBLLEFT_;
	g_needling = ISARG_RAFTER;
}
#endif

void				parser__link__colon(void) // -------------------------------: ;
{
	g_last_cmd->link = LINK_COLON_;
	g_needling = ISCMD;
}

void				parser__link__pipe(void) // --------------------------------: |
{
	g_last_cmd->link = LINK_PIPE__;
	g_needling = ISCMD;
}

void				parser__link__dblrafters_right(void) // --------------------: >>
{
	g_last_cmd->link = REDIR_DBLRIGHT;
	g_needling = ISARG_RAFTER;
}

void				parser__link__rafters_right(void) // -----------------------: >
{
	g_last_cmd->link = REDIR_RIGHT___;
	g_needling = ISARG_RAFTER;
}

void				parser__link__rafters_left(void) // ------------------------: <
{
	g_last_cmd->link = REDIR_LEFT____;
	g_needling = ISARG_RAFTER;
}

#if BONUS == ON

void				parser__link(int *i, int *j)
{
	if (g_line[*i] == ';')
		parser__link__colon();
	else if (g_line[*i] == '&' && g_line[*i + 1] == '&')	// BONUS
		parser__link__dbland();
	else if (g_line[*i] == '&')								// BONUS
		parser__link__and();
	else if (g_line[*i] == '|' && g_line[*i + 1] == '|')	// BONUS
		parser__link__dblor();
	else if (g_line[*i] == '|')
		parser__link__pipe();
	else if (g_line[*i] == '>' && g_line[*i + 1] == '>')
		parser__link__dblrafters_right();
	else if (g_line[*i] == '<' && g_line[*i + 1] == '<')	// BONUS
		parser__link__dblrafters_left();
	else if (g_line[*i] == '>')
		parser__link__rafters_right();
	else if (g_line[*i] == '<')
		parser__link__rafters_left();
}
#else
void				parser__link(int *i, int *j)
{
	if (g_line[*i] == ';')
		parser__link__colon();
	else if (g_line[*i] == '|')
		parser__link__pipe();
	else if (g_line[*i] == '>' && g_line[*i + 1] == '>')
		parser__link__dblrafters_right();
	else if (g_line[*i] == '>')
		parser__link__rafters_right();
	else if (g_line[*i] == '<')
		parser__link__rafters_left();
}
#endif

void				parser(void)
{
	int				i;
	int				j;

	i = 0;
	while (1)
	{
		pass_space(g_line, &i); // pass all spaces while isspace(g_line[i]) is true
		if (!g_line[i]) // id end of g_line, loop break
			break ;
		if (g_line[i] == '\\') // if backslash next char is a cmd or an arg
			parser__valid_char(&g_exp, g_line, &i, &j);
		if (g_line[i] == '\"' || g_line[i] == '\'') // strsub the string into quottes ["] will search next ["] and ['] will search next [']
			parser__quote(&g_exp, g_line, &i, &j);
		else if (ft_isspecial(g_line[i])) // & or | or ; or > or < // special effect
			parser__link(g_line[i], i);
		else
			parser__valid_char(&g_exp, g_line, &i, &j);
		i = j;
	}
}

void				preparser(int prompt)
{
	char			*str;
	char			*tmp;

	print_prompt(prompt);
	get_next_line(0, &str);
	if (str && ft_strlen(str))
	{
		tmp = ft_strjoin(g_line, str);
		try_free_(&g_line, _FL_);
		g_line = tmp;
	}
	try_free_(str, _FL_);
}

void				init(void)
{
	g_exp = try_malloc(sizeof(t_cmd), _FL_);
}

void				reset_exp(void)
{
	ft_del_list_np(&g_exp, __f__ft_del_node_np__t_arg__);
}

int					main(void)
{
	char			*raw_exp;
	init();
	while (1)
	{
		reset_exp(); // DONE // works ? TO TEST // norme OK !
		preparser(&raw_exp, PROMPT_NORMAL); // IN PROGRESS
		parser(raw_exp);
		process(); // TODO
	}
	return (0);
}
/*
output cmd:
	file:	">" || // O_WRONLY | O_TRUNC
			">>";  // O_WRONLY
	cmd:	"|"
input cmd:
	file:	'<';
*/
