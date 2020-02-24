/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 21:37:59 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/24 18:43:22 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// les terminaux doivent etre eaten et les non terminaux sont uniquement des fonction et donc appel de fonction



t_token		get_next_token()
{
	while (self.current_char != EOT)
	{
		if (isspace(self.current_char))
			skip_whitespace(self);

	}
}

int			nt_digit(self)
{

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
