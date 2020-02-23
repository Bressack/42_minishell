/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_is_hell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 00:17:15 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/24 00:41:28 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** generate a shell script
*/

# define	DBL_AND		1
# define	DBL_OR		1
# define	SGL_AND		1
# define	HEREDOC		1
# define	FD_REDIR	1

typedef struct		s_cmd
{
	char			name[1024];
	char			opt[20];
	char			arg[1024];
}					t_cmd;
typedef struct		s_redir
{
	char			type[3];
	char			arg[10][1024];
}					t_redir;

char				*redir[4] =
{
	">" ,
	">>",
	"<" ,
	"<<"
}

t_cmd				cmd =
{
	{}
}


int		main(void)
{

	return (0);
}

redir: [redir]

cmd: [cmd]

arg: [arg]

lexpr: [expr] ["&&"|"||" lexpr]

expr: [redir] [cmd [redir|arg]]



