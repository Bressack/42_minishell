/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 14:10:54 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/06 16:55:49 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ms.h>

char		*lexicon[20] =
{
	";",
	"<",	">",
	"<<",	">>",
	"|",	"||",
	"&",	"&&",
	"(",	")",
	NULL
};

int			isinlexicon(char *s)
{
	int		i;
	int		j;
	int		max;

	max = -1;
	i = 0;
	while (lexicon[i])
	{
		j = 0;
		while (lexicon[i][j] && lexicon[i][j] == s[j])
			j++;
		if (!lexicon[i][j])
			max = i;
		i++;
	}
	return (max);
}

// echo "ew"er'sdf'df;

void		add_to_lex(t_lex **lex, char *s, int len)
{
	t_lex	*new;

	new = try_malloc(sizeof(t_lex), _FL_);
	new->str = ft_strndup(s, len);
	ft_add_node_end_np((t_pnp **)lex, (t_pnp *)new);
}

int		lexer__frame(t_lex **lex, char *s, int end, int *start)
{
	if (s[end] && (s[end] == ' ' || s[end] == '\t'))
	{
		printf("%s found\n", s[end] == ' ' ? "space" : "tab");
		add_to_lex(lex, &s[(*start)], end - (*start));
		printf("[!] add_to_lex: [%.*s]\n", end - (*start), &s[(*start)]);
		while (s[++end] == ' ' || s[end] == '\t')
			;
		(*start) = end;
	}
	if (s[end] && s[end] == '\'')
	{
		printf("single frame\n");
		printf("     before : [%.*s]\n", end - (*start), &s[(*start)]);
		while (s[++end] != '\'')
			;
		end++;
		printf("     after  : [%.*s]\n", end - (*start), &s[(*start)]);
	}
	if (s[end] && s[end] == '\"')
	{
		printf("double frame\n");
		printf("     before : [%.*s]\n", end - (*start), &s[(*start)]);
		while (s[++end] != '\"')
			;
		end++;
		printf("     after  : [%.*s]\n", end - (*start), &s[(*start)]);
	}
	return (end);
}
// echo l"e"s 'amis'haha

t_lex		*lexer(char *s)
{
	t_lex	*lex;
	int		start;
	int		end;
	int		i;

	start = 0;
	end = 0;
	printf("lexer start with {%s}\n", s);
	while (1)
	{
		printf("current : [%.*s]\n", end - start, &s[start]);
		if (!s[end])
		{
			printf("end of s: breaking loop\n");
			add_to_lex(&lex, &s[start], end - start);
			printf("[!] add_to_lex: [%.*s]\n", end - start, &s[start]);
			break ;
		}
		end = lexer__frame(&lex, s, end, &start);
		if (s[end] && (i = isinlexicon(&s[start])) > -1)
		{
			printf("char in lexicon\n");
			if (end - start)
			{
				add_to_lex(&lex, &s[start], end - start);
				printf("[!] add_to_lex: [%.*s]\n", end - start, &s[start]);
			}
			add_to_lex(&lex, lexicon[i], ft_strlen(lexicon[i])); // add a new node in lex with the lexicon[i]'s string
			printf("[!] add_to_lex: [%.*s]\n", end - start, &s[start]);
			start += ft_strlen(lexicon[i]);
		}
		else
			end++;
	}
	return (lex);
}

// cat -e;ls -a -l .. >test1|ls>test2;echo "ok"|<test1<test2 echo $HOME '$HOME' "$HOME">>test3>test4
