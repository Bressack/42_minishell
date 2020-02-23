/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 21:37:59 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/23 22:03:43 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// les terminaux doivent etre eaten et les non terminaux sont uniquement des fonction et donc appel de fonction
int		nt_ascii()
{
	return (c >= 0 && c <= 254 ? 1 : 0);
}

int		nt_letter()
{
	return ((c >= 'a' && c <= 'z' )|| (c >= 'A' && c <= 'Z') ? 1 : 0);
}

int		nt_symbole()
{
	return (c == '!' || c == '#' || c == '%' || c == '+' || c == ',' ||
			c == '-' || c == '.' || c == ':' || c == '=' || c == '@' ||
			c == '[' || c == ']' || c == '^' || c == '_' || c == '`' ||
			c == '{' || c == '}' || c == '/' || c == '~' || c == '?' ||
			c == '*' ? 1 : 0);
}

int		nt_digit()
{
	return (c >= '0' && c <= '9' ? 1 : 0);
}

void		nt_number()
{
	return (nt_digit(c) || (nt_digit(c) && ));
}

void		nt_escaped()
{

}

void		nt_word()
{

}

void		nt_word_list()
{

}

void		nt_assignment_word()
{

}

void		nt_redirection()
{

}

void		nt_simple_command_element()
{

}

void		nt_redirection_list()
{

}

void		nt_simple_command()
{

}

void		nt_command()
{

}

void		nt_subshell()
{

}

void		nt_list()
{

}

void		nt_compound_list()
{

}

void		nt_list0()
{

}

void		nt_list1()
{

}

void		nt_list_terminator()
{

}

void		nt_newline_list()
{

}

void		nt_simple_list()
{

}

void		nt_simple_list1()
{

}

void		nt_pipeline()
{

}
