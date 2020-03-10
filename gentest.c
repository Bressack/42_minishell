/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gentest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 13:10:55 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/10 19:21:46 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libc.h>

char	*cmd[200][3][200] =
{
	{ { ""       , NULL }, { "", NULL                                                             } , { "" } },
	{ { "ls"     , NULL }, { "", "-l", "-1", "-l", "-a", "-G", "-h", "-o", "-s", "-t", "-Z", NULL } , { "file1", "file2", "file3", "file4", "dir1", "dir2", "dir3", "dir4", ".", "..", "~", "/" } },
	{ { "cat"    , NULL }, { "", "-e", NULL                                                       } , { "file1", "file2", "file3", "file4", "dir1", "dir2", "dir3", "dir4", ".", "..", "~", "/" } },
	{ { "head"   , NULL }, { "", "-c 100", NULL                                                   } , {  } },
	{ { "touch"  , NULL }, { "", "-c", NULL                                                       } , { "file1", "file2", "file3", "file4" } },
	{ { "rm"     , NULL }, { "", "-rf", NULL                                                      } , { "file1", "file2", "file3", "file4", "dir1", "dir2", "dir3", "dir4" } },
	{ { "wc"     , NULL }, { "", "-l", "-c", "-m", "-w", NULL                                     } , { "file1", "file2", "file3", "file4", "dir1", "dir2", "dir3", "dir4", ".", "..", "~", "/" } },
	{ { "test"   , NULL }, { "", "-f", NULL                                                       } , { "file1", "file2", "file3", "file4", "dir1", "dir2", "dir3", "dir4", ".", "..", "~", "/" } },
	{ { "echo"   , NULL }, { "", "-n", NULL                                                       } , { "", "\\n", "hej", "da", "salut", "#$#$%&&", "ls -l | cat", "ls!", "salut \'test\' coucou", "s\"v\"e\'n\'\'s\'k\"a\"", "a", "$HOME", "$HOME$", "$", "$1test", "$t1est", "$test1", "$$test", "$HHOME", "$HEJ", "$HEJ=\"DA\"", "echo", "$#t@e!s&t^*_-_3902840", "798453138681", "asdfcsdsdc", "____", "++", "==", "$=", "$=$$", "$?", "$$?", "?$", "$1?", "$?9", "@!$adas", "*&YT^%$" } },
	{ { "env"    , NULL }, { "", "-d", "-Z", NULL                                                 } , { "" } },
	{ { "export" , NULL }, { "", "-g", "-?", "-#", NULL                                           } , { "" } },
	{ { "cd"     , NULL }, { "", "-s", NULL                                                       } , {  } },
	{ {NULL     , NULL}, {NULL}}
}

char	*file[100] =
{
	"",
	"a",
	"b",
	"c",
	"test1",
	"test2",
	"test3",
	"test4",
	"test5",
	NULL
}

char	*redir[100] =
{
	"",
	">",
	">>",
	"<",
	NULL
}

char	*sep[100] =
{
	"",
	";",
	"&&",
	"||",
	"|",
	NULL
}

char	*space[100] =
{
	"",
	" ",
	"                 ",
	"\t",
	"\t  ",
	"\t                 ",
	"\t\t",
	"\t  \t",
	"\t                 \t",
}



int		main(void)
{
	srand(time(NULL));

	for (int i = 0; i < 20; i++) // nb cmd in the test (e.g. ls;ls|ls&&ls|ls are 5 cmd)
	{
		for (size_t j = 0; j < 5; j++) // nb redir before cmd
		{
			for (size_t k = 0; k < j; k++) // print j redir
			{
				printf("%s\n", );
			}
		}
	}
	return (0);
}
