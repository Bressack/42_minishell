/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 08:22:11 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/17 12:16:05 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token			token__new(t_token_type type, char *value, int pos)
{
	t_token		new;

	new.type = type;
	if (new.type != ERR && new.type != EOT)
	{
		new.value = value; // not a copy (if origin is freed, new.value will be freed too)
		if (new.value)
			new.len = ft_strlen(value);
		else
			new.len = 0;
		new.pos_in_line = pos;
	}
	else
		new.value = NULL;
	return (new);
}

void			token__del(t_token token)
{
	if (token.type == WORD)
		free(token.value);
}

void			token__print(t_token t)
{
	if (t.type == ERR)
		printf("[ "C_G_GREEN"TOKEN"C_RES" ] { "C_G_CYAN"type:"C_RES" "C_G_MAGENTA"ERR          "C_RES" } { "C_G_CYAN"value:"C_RES" ["C_G_MAGENTA"%s"C_RES"] }\n", t.value);
	else if (t.type == EOT)
		printf("[ "C_G_GREEN"TOKEN"C_RES" ] { "C_G_CYAN"type:"C_RES" "C_G_MAGENTA"EOT          "C_RES" } { "C_G_CYAN"value:"C_RES" ["C_G_MAGENTA"%s"C_RES"] }\n", t.value);
	else if (t.type == SPACE)
		printf("[ "C_G_GREEN"TOKEN"C_RES" ] { "C_G_CYAN"type:"C_RES" "C_G_MAGENTA"SPACE        "C_RES" } { "C_G_CYAN"value:"C_RES" ["C_G_MAGENTA"%s"C_RES"] }\n", t.value);
	else if (t.type == WORD)
		printf("[ "C_G_GREEN"TOKEN"C_RES" ] { "C_G_CYAN"type:"C_RES" "C_G_MAGENTA"WORD         "C_RES" } { "C_G_CYAN"value:"C_RES" ["C_G_MAGENTA"%s"C_RES"] }\n", t.value);
	else if (t.type == LPAREN)
		printf("[ "C_G_GREEN"TOKEN"C_RES" ] { "C_G_CYAN"type:"C_RES" "C_G_MAGENTA"LPAREN       "C_RES" } { "C_G_CYAN"value:"C_RES" ["C_G_MAGENTA"%s"C_RES"] }\n", t.value);
	else if (t.type == RPAREN)
		printf("[ "C_G_GREEN"TOKEN"C_RES" ] { "C_G_CYAN"type:"C_RES" "C_G_MAGENTA"RPAREN       "C_RES" } { "C_G_CYAN"value:"C_RES" ["C_G_MAGENTA"%s"C_RES"] }\n", t.value);
	else if (t.type == REDIREC_IN)
		printf("[ "C_G_GREEN"TOKEN"C_RES" ] { "C_G_CYAN"type:"C_RES" "C_G_MAGENTA"REDIREC_IN   "C_RES" } { "C_G_CYAN"value:"C_RES" ["C_G_MAGENTA"%s"C_RES"] }\n", t.value);
	else if (t.type == REDIREC_OUT)
		printf("[ "C_G_GREEN"TOKEN"C_RES" ] { "C_G_CYAN"type:"C_RES" "C_G_MAGENTA"REDIREC_OUT  "C_RES" } { "C_G_CYAN"value:"C_RES" ["C_G_MAGENTA"%s"C_RES"] }\n", t.value);
	else if (t.type == DREDIREC_OUT)
		printf("[ "C_G_GREEN"TOKEN"C_RES" ] { "C_G_CYAN"type:"C_RES" "C_G_MAGENTA"DREDIREC_OUT "C_RES" } { "C_G_CYAN"value:"C_RES" ["C_G_MAGENTA"%s"C_RES"] }\n", t.value);
	else if (t.type == SQUOTE)
		printf("[ "C_G_GREEN"TOKEN"C_RES" ] { "C_G_CYAN"type:"C_RES" "C_G_MAGENTA"SQUOTE       "C_RES" } { "C_G_CYAN"value:"C_RES" ["C_G_MAGENTA"%s"C_RES"] }\n", t.value);
	else if (t.type == DQUOTE)
		printf("[ "C_G_GREEN"TOKEN"C_RES" ] { "C_G_CYAN"type:"C_RES" "C_G_MAGENTA"DQUOTE       "C_RES" } { "C_G_CYAN"value:"C_RES" ["C_G_MAGENTA"%s"C_RES"] }\n", t.value);
	else if (t.type == DBL_AND)
		printf("[ "C_G_GREEN"TOKEN"C_RES" ] { "C_G_CYAN"type:"C_RES" "C_G_MAGENTA"DBL_AND      "C_RES" } { "C_G_CYAN"value:"C_RES" ["C_G_MAGENTA"%s"C_RES"] }\n", t.value);
	else if (t.type == DBL_OR)
		printf("[ "C_G_GREEN"TOKEN"C_RES" ] { "C_G_CYAN"type:"C_RES" "C_G_MAGENTA"DBL_OR       "C_RES" } { "C_G_CYAN"value:"C_RES" ["C_G_MAGENTA"%s"C_RES"] }\n", t.value);
	else if (t.type == PIPE)
		printf("[ "C_G_GREEN"TOKEN"C_RES" ] { "C_G_CYAN"type:"C_RES" "C_G_MAGENTA"PIPE         "C_RES" } { "C_G_CYAN"value:"C_RES" ["C_G_MAGENTA"%s"C_RES"] }\n", t.value);
	else if (t.type == SEMICON)
		printf("[ "C_G_GREEN"TOKEN"C_RES" ] { "C_G_CYAN"type:"C_RES" "C_G_MAGENTA"SEMICON      "C_RES" } { "C_G_CYAN"value:"C_RES" ["C_G_MAGENTA"%s"C_RES"] }\n", t.value);
	else
		printf("[ "C_G_GREEN"TOKEN"C_RES" ] { "C_G_CYAN"type:"C_RES" "C_G_MAGENTA"INVALID      "C_RES" } { "C_G_CYAN"value:"C_RES" ["C_G_MAGENTA"NULL"C_RES"] }\n");
}

/*
echo "les amis 'je suis la' et aussi les canards" les petit 'paingouin'"des iles"aussi""des hommes"'et'des'femmes';ls
*/