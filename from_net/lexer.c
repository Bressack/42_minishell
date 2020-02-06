/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:11:19 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/03 17:15:06 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_lexer		*get_return(t_list *tokenlst, t_state state, int i)
{
	t_lexer  *lexed;

	if (tokenlst == NULL)
		return (NULL);
	lexed = (t_lexer *)malloc(sizeof(t_lexer));
	if (lexed == NULL)
	{
		destroy_tokenlst(&tokenlst);
		return (NULL);
	}
	lexed->tokenlst = tokenlst;
	if (state.curr >= Standard)
	{
		lexed->err = None;
		lexed->err_index = -1;
		lexed->err_type = None;
	}
	else
	{
		lexed->err = state.curr;
		lexed->err_index = i;
		lexed->err_type = (t_type)state.old;
	}
	return (lexed);
}

static t_list		*get_token(t_type type, char *str, int i, int len)
{
	t_list  *token;
	t_token  data;

	data.type = type;
	data.value = ft_strsub(str, i, len);
	if (data.value == NULL)
		return (NULL);
	else
	{
		token = ft_lstnew((void *)&data, sizeof(t_token));
		if (token == NULL)
			free(data.value);
	}
	return (token);
}

int					maj_tokenlst(t_list **atokenlst, t_state state, char *str, int i)
{
	static int len = 1;
	t_list  *token;

	if (state.old == state.curr && str[i] != '\0')
		len++;
	else
	{
		token = get_token((t_type)state.old, str, (i - len), len);
		if (token == NULL)
		{
			destroy_tokenlst(atokenlst);
			return (0);
		}
		ft_lstadd(atokenlst, token);
		len = 1;
	}
	return (1);
}

t_lexer				*str_lex(char *str)
{
	t_func  rules_tab[RULES];
	t_list  *tokenlst;
	t_state  state;
	int  i;
	int  ret;

	init_rules_tab(rules_tab);
	tokenlst = NULL;
	state.old = Standard;
	i = 0;
	ret = 1;
	while (str[INDEX] != '\0')
	{
		state.curr = rules_tab[state.old](str, i);
		if (state.old != Standard)
			ret = maj_tokenlst(&tokenlst, state, str, i);
		if (ret == 0 || state.curr < Standard)
			return (get_return(tokenlst, state, i));
		state.old = state.curr;
		i++;
	}
	return (get_return(tokenlst, state, i));
}
