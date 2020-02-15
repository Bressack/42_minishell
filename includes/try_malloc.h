/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_malloc.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 00:38:51 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/15 13:47:30 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRY_MALLOC_H
# define TRY_MALLOC_H
# include <minishell.h>
# ifndef __SIZE_MALLOC_DEBUG
#  define __SIZE_MALLOC_DEBUG	1000000
# endif
# define _FL_ (char *)__FUNCTION__, (int)__LINE__
# define MEM_USED_BY_DEBUG (size_t)(sizeof(t_debug_malloc) * __SIZE_MALLOC_DEBUG) + sizeof(t_debug_malloc) + (sizeof(size_t) * 2)
# define GDM g_debug_malloc[i]
typedef struct			s_debug_malloc
{
	void				*mem;
	int					size;
	int					real_size;
	char				*f_malloc;
	int					l_malloc;
	char				*f_free;
	int					l_free;
	int					nb_free;
}						t_debug_malloc;
extern t_debug_malloc	g_debug_malloc[__SIZE_MALLOC_DEBUG];
extern size_t			g_i_malloc;
extern int				__test;
void					print_mem__(void);
void					*try_malloc(size_t size, char *f, int l);
void					try_free_(void **p, char *f, int l);
void					try_free_all(char *f, int l);
#endif
