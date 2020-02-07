/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtrace_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 17:14:37 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/07 17:32:42 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libc.h>
#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BT_BUF_SIZE 100

void	fun_a(void);
void	fun_b(void);
void	fun_c(void);
void	fun_d(void);
void	fun_e(void);
void	fun_f(void);
void	fun_g(void);

void	fun_a(void) {fun_b();}
void	fun_b(void) {fun_c();}
void	fun_c(void) {fun_d();}
void	fun_d(void) {fun_e();}
void	fun_e(void) {fun_f();}
void	fun_f(void) {fun_g();}
void	fun_g(void)
{
	int nptrs;
	void *buf[BT_BUF_SIZE];
	char **str;

	nptrs = backtrace(buf, BT_BUF_SIZE);
	str = backtrace_symbols(buf, nptrs);
	for (int i = 0; i < nptrs; i++)
		printf("%s\n", str[i]);
}

int		main(void)
{
	fun_a();
	return (0);
}


// main > fun_a > fun_b > fun_c > fun_d > fun_e >