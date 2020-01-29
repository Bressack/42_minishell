/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 17:17:28 by tharchen          #+#    #+#             */
/*   Updated: 2020/01/29 23:29:48 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ms.h>
#include <libc.h>
#include <stdlib.h>
#include <get_next_line.h>

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

int					ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\r' ||
			c == '\v' || c == '\f' || c == ' ');
}

void				__f__ft_del_node_np__t_arg__(t_pnp *a)
{
	try_free_((void **)&((t_arg *)a)->name, _FL_);
}

void				__f__ft_del_node_np__t_cmd__(t_pnp *a)
{
	try_free_((void **)&((t_arg *)a)->name, _FL_);
	ft_del_list_np((t_pnp **)&((t_cmd *)a)->av, __f__ft_del_node_np__t_arg__);
}

void				add_new_arg(char *data, int type, va_list ap)
{
	t_arg			*new;

	new = try_malloc(sizeof(t_arg), _FL_);
	new->name = data;
	new->isquote = va_arg(ap, int);
	new->quote_state = va_arg(ap, int);
	if (type == ISARG_IN)
	{
		ft_add_node_end_np((t_pnp **)(&g_av_in), (t_pnp *)new);
		!new ? g_last_cmd->av_in = new : 0;
	}
	else if (type == ISARG_OUT)
	{
		ft_add_node_end_np((t_pnp **)(&g_av_out), (t_pnp *)new);
		!new ? g_last_cmd->av_out = new : 0;
	}
	else
	{
		ft_add_node_end_np((t_pnp **)(&g_av), (t_pnp *)new);
		!new ? g_last_cmd->av = new : 0;
	}
	g_last_arg = new; // IDKIIIU
}

void				add_new_cmd(char *data, va_list ap)
{
	t_cmd			*new;

	new = try_malloc(sizeof(t_cmd), _FL_);
	new->name = data;
	new->fd_in = FD_STDIN;
	new->fd_out = FD_STDOUT;
	new->av_in = g_av_in;
	new->av_out = g_av_out;
	new->av = g_av;
	new->isquote = va_arg(ap, int);
	new->quote_state = va_arg(ap, int);
	ft_add_node_end_np((t_pnp **)&g_exp, (t_pnp *)new);
	g_last_cmd = new;
}

				//  new_element(data, ISARG     , QUOTE_OPEN || QUOTE_CLOSE);
				//  new_element(data, ISARG_IN  , QUOTE_OPEN || QUOTE_CLOSE);
				//  new_element(data, ISARG_OUT , QUOTE_OPEN || QUOTE_CLOSE);
				//  new_element(data, ISCMD     , QUOTE_OPEN || QUOTE_CLOSE);
void				new_element(char *data, int type, ...)
{
	va_list			ap;

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

#ifdef BONUS // ft_isspecial bonus

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
	(void)i; // i IS NOT USED
}

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
		if (g_line[(*j) - 1] != '\\' && g_line[(*j)] == g_line[(*i)])
			break ;
		if (g_line[(*j)] == '\\')
			(*j) += 2;
		else
			(*j)++;
	}
	new_element(ft_strndup(&g_line[(*i)], (*j) - (*i)), g_needling, ISQUOTE,
		!g_line[(*j)] ? QUOTE_OPEN : QUOTE_CLOSE);
	pass_space(i);
}

void				parser__valid_char(int *i, int *j)
{
	(*j) = (*i) + 1;
	while (g_line[(*j)] && !ft_isspecial(&g_line[(*j)]) && !ft_isspace(g_line[(*j)]))
	{
		if (ft_isquote(g_line[(*j)]) && pass_quotes(i, j) == QUOTE_OPEN)
		{
			preparser(PROMPT_NEXT_NEEDED);
			break ;
		}
		else
			(*j)++;
	}
	new_element(ft_strndup(&g_line[*i], (*j) - (*i)), g_needling, ISNOTQUOTE,
		QUOTE_CLOSE);
	g_needling = ISARG;
	pass_space(i);
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

void				parser__special__dbland(void) // ------------------------------: &&	BONUS
{
	g_last_cmd->link = LINK_AND;
	cmd_stop(ISCMD);
}

void				parser__special__and(void) // ---------------------------------: &		BONUS
{
	g_last_cmd->link = LINK_THREAD;
	cmd_stop(ISCMD);
}

void				parser__special__dblor(void) // -------------------------------: ||	BONUS
{
	g_last_cmd->link = LINK_OR;
	cmd_stop(ISCMD);
}

void				parser__special__dblrafters_left(void) // ---------------------: <<	BONUS
{
	g_last_cmd->link = REDIR_DBLLEFT;
	g_needling = ISARG_RAFTER;
}
#endif

void				parser__special__colon(void) // -------------------------------: ;
{
	g_last_cmd->link = LINK_COLON;
	cmd_stop(ISCMD);
}

void				parser__special__pipe(void) // --------------------------------: |
{
	g_last_cmd->link = LINK_PIPE;
	cmd_stop(ISCMD);
}

void				parser__special__dblrafters_right(void) // --------------------: >>
{
	g_last_cmd->open_flags = O_WRONLY|O_CREAT;
	g_last_cmd->open_flags_rights = OPEN__FLAG_O_CREAT__RIGHTS;
	g_needling = ISARG_OUT;
}

void				parser__special__rafters_right(void) // -----------------------: >
{
	g_last_cmd->open_flags = O_WRONLY|O_CREAT|O_TRUNC;
	g_last_cmd->open_flags_rights = OPEN__FLAG_O_CREAT__RIGHTS;
	g_needling = ISARG_OUT;
}

void				parser__special__rafters_left(void) // ------------------------: <
{
	g_last_cmd->open_flags = O_RDONLY;
	g_needling = ISARG_IN;
}

#ifdef BONUS

void				parser__special(int *i, int *j)
{
	if (g_line[*i] == ';')
		parser__special__colon();
	else if (g_line[*i] == '&' && g_line[*i + 1] == '&')	// BONUS
		parser__special__dbland();
	else if (g_line[*i] == '&')								// BONUS
		parser__special__and();
	else if (g_line[*i] == '|' && g_line[*i + 1] == '|')	// BONUS
		parser__special__dblor();
	else if (g_line[*i] == '|')
		parser__special__pipe();
	else if (g_line[*i] == '>' && g_line[*i + 1] == '>')
		parser__special__dblrafters_right();
	else if (g_line[*i] == '<' && g_line[*i + 1] == '<')	// BONUS
		parser__special__dblrafters_left();
	else if (g_line[*i] == '>')
		parser__special__rafters_right();
	else if (g_line[*i] == '<')
		parser__special__rafters_left();
}
#else
void				parser__special(int *i, int *j)
{
	if (g_line[*i] == ';')
		parser__special__colon();
	else if (g_line[*i] == '|')
		parser__special__pipe();
	else if (g_line[*i] == '>' && g_line[*i + 1] == '>')
		parser__special__dblrafters_right();
	else if (g_line[*i] == '>')
		parser__special__rafters_right();
	else if (g_line[*i] == '<')
		parser__special__rafters_left();
	*j += 2;
}
#endif

void				parser(void)
{
	int				i;
	int				j;

	i = 0;
	j = 0;
	while (1)
	{
		if (!g_line[i]) // end of g_line, loop break
			break ;
		pass_space(&i); // pass all spaces while isspace(g_line[i]) is true
		if (g_line[i] == '\\') // if backslash next char is a cmd or an arg
			parser__valid_char(&i, &j);
		if (g_line[i] == '\"' || g_line[i] == '\'') // strsub the string into quottes ["] will search next ["] and ['] will search next [']
			parser__quote(&i, &j);
		else if (ft_isspecial(&g_line[i])) // & or | or ; or > or < // special effect
			parser__special(&i, &j);
		else
			parser__valid_char(&i, &j);
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
		tmp = ft_strjoin(2, g_line, str);
		try_free_((void **)&g_line, _FL_);
		g_line = tmp;
	}
	try_free_((void **)&str, _FL_);
}

void				init(void)
{
	// MAYBE NOT USEFULL
}

void				reset_exp(void)
{
	ft_del_list_np((t_pnp **)&g_exp, __f__ft_del_node_np__t_cmd__);
}

void				debug__print_data(void)
{
	dprintf(2, "info exp:\n");
	for (t_cmd *tmp = g_exp; tmp; tmp = tmp->next)
	{
		dprintf(2, "cmd: \'%s\'\n", tmp->name);
		for (t_arg *tmp2 = tmp->av_in; tmp2; tmp2 = tmp2->next)
		{
			dprintf(2, "     av_in : %s\n", tmp2->name);
		}
		for (t_arg *tmp2 = tmp->av; tmp2; tmp2 = tmp2->next)
		{
			dprintf(2, "     av    : %s\n", tmp2->name);
		}
		for (t_arg *tmp2 = tmp->av_out; tmp2; tmp2 = tmp2->next)
		{
			dprintf(2, "     av_out: %s\n", tmp2->name);
		}
	}

}

int					main(void)
{
	// init();
	while (1)
	{
		reset_exp(); // DONE // works ? TO TEST // norme OK !
		preparser(PROMPT_NORMAL); // IN PROGRESS
		parser();
		debug__print_data();
		// process(); // TODO
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
