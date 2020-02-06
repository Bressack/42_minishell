/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:19:54 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/06 15:20:24 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
typedef struct		s_lex
{
	struct s_lex	*next;
	struct s_lex	*prev;
	char			*str;
}					t_lex;
t_lex		*lexer(char *s);
#endif
