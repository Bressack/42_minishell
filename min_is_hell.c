/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_is_hell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 00:17:15 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/24 17:17:48 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** generate a shell script
*/

#include <libc.h>

# define	TEST_DIR	"./minis_hell__test_dir"

# define	NB_REDIR		3
# define	NB_BUILTIN		7
# define	NB_CMD			6
# define	NB_OPT			10
# define	NB_ARG			10
# define	NB_FILE			10


# define	DBL_AND			1
# define	DBL_OR			1

typedef struct		s_cmd
{
	char			name[1024];
	char			opt[10][20];
	char			arg[10][1024];
}					t_cmd;
typedef struct		s_redir
{
	char			type[3];
	char			arg[10][1024];
}					t_redir;

char				*g_redir[NB_REDIR] =
{
	">" ,
	">>",
	"<"
}

char				*g_file[NB_FILE] =
{
	"a",
	"b",
	"c",
	"a/1",
	"a/2",
	"a/3",
	"a/1/a",
	"a/1/b",
	"a/1/b/1",
	"a/1/b/2"
}

t_cmd				g_builtins[NB_BUILTIN] =
{
	{"echo"		, {"-n", "", "", "", "", "", "", "", "", ""}, {"$HOME", "$PATH", "$a", "YQOWIUEYOQUIhuiahsiduhsdjkalhsdouieryquieyrwiuyrIUYIUWREYOWIUERY", "a", "3oqwieury", "_", "$f", "$g", "$QUIOWEYQOWIUEYOQUIhuiahsiduhsdjkalhsdouieryquieyrwiuyrIUYIUWREYOWIUERYWEOIRYWEORYWEOIURYEW_________________187263458167235486712ghjg312khj4g1k2jh3g4k2jh3g4"}},
	{"cd"		, {"", "", "", "", "", "", "", "", "", ""}, {"a", "b", "c", "a/1", "a/2", "a/3", "a/1/a", "a/1/b", "a/1/b/1", "a/1/b/2"}},
	{"pwd"		, {"", "", "", "", "", "", "", "", "", ""}, {"", "", "", "", "", "", "", "", "", ""}},
	{"export"	, {"", "", "", "", "", "", "", "", "", ""}, {"a", "b", "c", "d", "e", "f", "g", "ceciestunlongnomdevariablecarouijesuisungrosfilsdep", maisjepeuxetreencorepluscasscouillecarjenemetpasdespacenidapostrophedansmesphraseetcesttrescompliquealiresurtoutsijeparleensmspaskectropafacil2lirdesfrazemalekrit}},
	{"unset"	, {"", "", "", "", "", "", "", "", "", ""}, {"a", "b", "c", "d", "e", "f", "PWD", "ceciestunlongnomdevariablecarouijesuisungrosfilsdep", maisjepeuxetreencorepluscasscouillecarjenemetpasdespacenidapostrophedansmesphraseetcesttrescompliquealiresurtoutsijeparleensmspaskectropafacil2lirdesfrazemalekrit}},
	{"env"		, {"", "", "", "", "", "", "", "", "", ""}, {"", "", "", "", "", "", "", "", "", ""}},
	{"exit"		, {"", "", "", "", "", "", "", "", "", ""}, {"1", "-1", "-127", "2147483647", "-2147483648", "21474836472147483647", "-2147483647214748364721474836472147483647", "214748364721474836472147483647214748364721474836472147483647214748364721474836472147483647214748364721474836472147483647214748364721474836472147483647214748364721474836472147483647214748364721474836472147483647", "-214748364721474836472147483647214748364721474836472147483647214748364721474836472147483647214748364721474836472147483647214748364721474836472147483647214748364721474836472147483647214748364721474836472147483647214748364721474836472147483647", "0"}},
}

t_cmd				g_cmd[NB_CMD] =
{//   cmd          opt                                       arg
	{"ls"		, {"-l", "-a", "-g", "-G", "-1", "-R", "-o", "-A", "-s", "-1agGlRoAsh"}, {"test", TEST_DIR, "./", "../", "./../", "./../"TEST_DIR, "../TEST_DIR", "testd0/testd0/testf0", "testd0", "testd0/testd0"}},
	{"cat"		, {"", "", "", "", "", "", "", "", "", ""},      {"f1", "f2", "a/f1", "a/f2", "a/1/a/f1", "a/1/a/f2", "a/1/b/2/f1", "a/1/b/2/f2", "a/1/b/2/f3", "a/3/f1"}},
	{"wc"		, {"-l", "", "", "", "", "", "", "", "", ""},    {"f1", "f2", "a/f1", "a/f2", "a/1/a/f1", "a/1/a/f2", "a/1/b/2/f1", "a/1/b/2/f2", "../", "./"}},
	{"rm"		, {"-r", "-rf", "", "", "", "", "", "", "", ""}, {"a", "b", "c", "a/1", "a/2", "a/3", "a/1/a", "a/1/b", "a/1/b/1", "a/1/b/2"}},
	{"touch"	, {"", "", "", "", "", "", "", "", "", ""},      {"f1", "f2", "a/f1", "a/f2", "a/1/a/f1", "a/1/a/f2", "a/1/b/2/f1", "a/1/b/2/f2", "a/1/b/2/f3", "a/3/f1"}},
	{"mkdir"	, {"", "", "", "", "", "", "", "", "", ""},      {"a", "b", "c", "a/1", "a/2", "a/3", "a/1/a", "a/1/b", "a/1/b/1", "a/1/b/2"}},
}

void	compile_minishell(void)
{
	dprintf(fd, "./make re\n");
}

void	run_minishell(void)
{
	dprintf(fd, "./$1\n");
}

void	run_expr(char *expr)
{
	dprintf(fd, "%s\n", expr);
}

void	exit_minishell(void)
{
	dprintf(fd, "exit\n");
}

// ************************************************************************** //

redir: [redir file]

file: [file]

cmd: [cmd opt arg]

opt: [opt]

arg: [arg]

expr: [redir] [cmd [redir|arg]]

lexpr: [expr] ["&&" | "||" | "|" lexpr] [ ";" [expr]]

int			redir(int optionnal)
{
	static int	redir = 0;

	while (redir <= NB_REDIR - optionnal)
	{
		if (redir < NB_REDIR)
		{
			printf("%s ", g_redir[redir]);
			file(0);
		}
		redir++;
		return (redir < NB_REDIR);
	}
	return (0);
}

int			file(int optionnal)
{
	static int	file = 0;

	while (file <= NB_FILE - optionnal)
	{
		if (file < NB_FILE)
			printf("%s ", g_file[file]);
		file++;
		return (file < NB_FILE);
	}
	return (0);
}

int			cmd(int optionnal)
{
	static int	cmd = 0;

	while (cmd <= NB_CMD - optionnal)
	{
		if (cmd < NB_CMD)
			printf("%s ", g_cmd[cmd]);
		cmd++;
		return (cmd < NB_CMD);
	}
	return (0);
}

int			arg(int optionnal)
{
	static int	arg = 0;

	while (arg <= NB_ARG - optionnal)
	{
		if (arg < NB_ARG)
			printf("%s ", g_arg[arg]);
		arg++;
		return (arg < NB_ARG);
	}
	return (0);
}

int			expr(int optionnal)
{
	static int expr;
	static int i;

	redir(1);
	if (cmd(1))
	{
		while (i < 20)
		{

			i++;
			return (1);
		}

	}
}

char		*lexpr(int optionnal)
{

}

// ************************************************************************** //

void	brutforceHD(void)
{

}

// ************************************************************************** //

int		main(void)
{
	srand(time(NULL));

	compile_minishell();
	run_minishell();
	run_expr();
	exit_minishell();
	return (0);
}



