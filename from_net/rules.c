/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:15:40 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/03 17:16:32 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_vstate  rules_standard(char *str, int i)
{
	if (ft_strchr(STANDARD, str[i]))
		return (Standard);
	else if (ft_strchr(ESCAPMENT, str[i]))
		return (InEscapment);
	else if (ft_strchr(SEPARATOR, str[i]))
		return (InSeparator);
	else if (ft_strchr(REDIRECTOR, str[i]))
		return (InRedirector);
	else if (ft_strchr(FRAME, str[i]))
		return (InFrame);
	else if (ft_isprint(str[i]) != 0)
		return (InIdentifier);
	return (InLexError);
}

t_vstate  rules_escapment(char *str, int i)
{
	static int len = 1;

	if (len == 1)
	{
		len++;
		return (InEscapment);
	}
	else if (ft_strchr(STANDARD, str[i]))
		return (len = 1, Standard);
	else if (ft_strchr(ESCAPMENT, str[i]))
		return (len = 1, InEscapment);
	else if (ft_strchr(SEPARATOR, str[i]))
		return (len = 1, InSeparator);
	else if (ft_strchr(REDIRECTOR, str[i]))
		return (len = 1, InRedirector);
	else if (ft_strchr(FRAME, str[i]))
		return (len = 1, InFrame);
	else if (ft_isprint(str[i]) != 0)
		return (len = 1, InIdentifier);
	return (InLexError);

}

t_vstate  rules_identifier(char *str, int i)
{
	if (ft_strchr(STANDARD, str[i]))
		return (Standard);
	else if (ft_strchr(ESCAPMENT, str[i]))
		return (InEscapment);
	else if (ft_strchr(SEPARATOR, str[i]))
		return (InSeparator);
	else if (ft_strchr(REDIRECTOR, str[i]))
		return (InRedirector);
	else if (ft_strchr(FRAME, str[i]))
		return (InFrame);
	else if (ft_isprint(str[i]) != 0)
		return (InIdentifier);
	return (InLexError);
}

t_vstate  rules_frame(char *str, int i)
{
	static int len = 1;
	static char c;

	if (len == 1)
	{
		c = str[i - 1];
		return (++len, (str[i] == '\0') ? InLexError : InFrame);
	}
	else if (str[i] == '\0' && c != '\0')
		return (InLexError);
	else if ((str[i] != c && c != '\0') || (str[i] == c && str[i - 1] == '\\'))
		return (InFrame);
	else if (str[i] == c)
		return (c = '\0', InFrame);
	else if (ft_strchr(STANDARD, str[i]))
		return (len = 1, Standard);
	else if (ft_strchr(ESCAPMENT, str[i]))
		return (len = 1, InEscapment);
	else if (ft_strchr(SEPARATOR, str[i]))
		return (len = 1, InSeparator);
	else if (ft_strchr(REDIRECTOR, str[i]))
		return (len = 1, InRedirector);
	else if (ft_isprint(str[i]) != 0)
		return (len = 1, InIdentifier);
	return (InLexError);
}

t_vstate  rules_separator(char *str, int i)
{
	static int len = 1;

	if (ft_strchr(SEPARATOR, str[i]) && str[i] != '\0')
	{
		len++;
		if ((len == 2 && (str[i] != str[i - 1] || str[i] == ';')) || len > 2)
			return (InLexError);
		return (InSeparator);
	}
	else if (ft_strchr(STANDARD, str[i]))
		return (len = 1, Standard);
	else if (ft_strchr(ESCAPMENT, str[i]))
		return (len = 1, InEscapment);
	else if (ft_strchr(REDIRECTOR, str[i]))
		return (InSynError);
	else if (ft_strchr(FRAME, str[i]))
		return (len = 1, InFrame);
	else if (ft_isprint(str[i]) != 0)
		return (len = 1, InIdentifier);
	return (InLexError);
}

t_vstate  rules_redirector(char *str, int i)
{
	static int len = 1;

	if (ft_strchr(REDIRECTOR, str[i]) && str[i] != '\0')
	{
		len++;
		if ((len == 2 && (str[i] != str[i - 1] || str[i] == '|')) || len > 2)
			return (InLexError);
		return (InRedirector);
	}
	else if (ft_strchr(STANDARD, str[i]))
		return (len = 1, Standard);
	else if (ft_strchr(ESCAPMENT, str[i]))
		return (len = 1, InEscapment);
	else if (ft_strchr(SEPARATOR, str[i]))
		return (InSynError);
	else if (ft_strchr(FRAME, str[i]))
		return (len = 1, InFrame);
	else if (ft_isprint(str[i]) != 0)
		return (len = 1, InIdentifier);
	return (InLexError);
}
