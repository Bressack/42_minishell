/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 14:10:54 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/07 19:22:26 by tharchen         ###   ########.fr       */
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

	printf("searching for spec: ");
	max = -1;
	i = 0;
	while (lexicon[i])
	{
		j = 0;
		printf("lexicon[i][j]: {%d}:(%c)\n", lexicon[i][j], lexicon[i][j]);
		while (s[j] && lexicon[i][j] && lexicon[i][j] == s[j])
			j++;
		printf("lexicon[i][j]: {%d}:(%c)\n\n", lexicon[i][j], lexicon[i][j]);
		if (!lexicon[i][j])
			max = i;
		i++;
	}
	if (max == -1)
		printf("no match\n");
	else
		printf("matched: [%s]\n", lexicon[max]);
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
	lex = NULL;
	printf(""C_G_GREEN"lexer:"C_G_WHITE" start with {"C_G_RED"%s"C_G_WHITE"}"C_RES"\n", s);
	while (s)
	{
		printf("current : [%.*s]\n", end - start, &s[start]);
		if (!s[end])
		{
			printf(""C_G_GREEN"lexer:"C_G_WHITE" end"C_RES"\n");
			add_to_lex(&lex, &s[start], end - start);
			printf("[!] add_to_lex: [%.*s]\n", end - start, &s[start]);
			break ;
		}
		end = lexer__frame(&lex, s, end, &start);
		if (s[end] && (i = isinlexicon(&s[end])) > -1)
		{
			printf("char in lexicon\n");
			if (end - start)
			{
				add_to_lex(&lex, &s[start], end - start - 1);
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
