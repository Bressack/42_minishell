/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   very_stupid_calculator.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 04:16:01 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/24 00:16:49 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libc.h>
#define DIV			3

char	optab[5] =
{
	'+',
	'-',
	'*',
	'/',
	'%'
};

int		tot;

#define MAX_CALC	2000

void	do_what_you_should_to_do_madgod_blaze()
{
	char	op = '+';

	tot = 0;
	printf("double\t\tcalc(int a, char op, int b)\n{\n\n");
	for (int a = 0; a < MAX_CALC; a++)
	{
		for (int b = 0; b < MAX_CALC; b++)
		{
			for (int i = 0; i < 5; i++)
			{
				if (i >= DIV && !b)
					continue ;
				tot++;
				op = optab[i];
				printf("\tif (a == %d && op == \'%c\' && b == %d) { return (%sa %c %sb);}\n",
				a,
				op,
				b,
				i > DIV ? "" : "(double)",
				op,
				i > DIV ? "" : "(double)"
				);
			}
		}
	}
	printf("\tdprintf(2, \"syntax error\\n\");\n\texit(-1);\n");
	printf("}\n\n");
}

int		main(void)
{
	printf("\n#include <libc.h>\n\n");
	do_what_you_should_to_do_madgod_blaze();
	printf("\
int\t\t\tmain(int ac, char **av)\n\
{\n\
\tdouble\tret;\n\
\tint\t\ta;\n\
\tchar\top;\n\
\tint\t\tb;\n\n\
\tif (ac != 4 || av[2][1])\n\
\t{\n\
\t\tdprintf(2, \"args error\\n\");\n\t\texit(-1);\n\
\t}\n\
\ta = atoi(av[1]);\n\
\top = av[2][0];\n\
\ta = atoi(av[3]);\n\
\tret = 0;\n\
\tret = calc(a, op, b);\n\
\tprintf(\"after %d if , the good result is: %%f\\n\", ret);\n\
\treturn (0);\n\
}\n\
\n", tot);
	return (0);
}

// \tscanf(\"%%d %%c %%d\", &a, &op, &b);\n\