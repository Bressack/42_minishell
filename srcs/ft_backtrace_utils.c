/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_backtrace_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 16:14:09 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/17 02:22:49 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libc.h>
#include <execinfo.h>
#include <stdio.h>

void		bt(void)
{
	void	*callstack[128];
	int		i;
	int		frames;
	char	**strs;

	frames = backtrace(callstack, 128);
	strs = backtrace_symbols(callstack, frames);

	for (i = 0; i < frames; ++i)
	{
		printf("%s\n", strs[i]);
	}
	free(strs);
}

// char		*bt_get_caller(void)
// {
//
// }
//
// char		*bt_get_fullstack(void)
// {
//
// }
//
// char		*bt_get_nstack(void)
// {
//
// }

void	fun_e(void) {bt();}
void	fun_d(void) {fun_e();}
void	fun_c(void) {fun_d();}
void	fun_b(void) {fun_c();}
void	fun_a(void) {fun_b();}

int		main(void)
{
	fun_a();
	return (0);
}
