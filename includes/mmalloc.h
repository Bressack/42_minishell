/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmalloc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 19:25:01 by frlindh           #+#    #+#             */
/*   Updated: 2020/03/08 12:17:19 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MMALLOC_H
# define MMALLOC_H

typedef struct		s_list
{
	void			*data;
	struct s_list	*next;
}					t_list;

extern t_list		*g_all_malloc;

void				*mmalloc(unsigned int size);
void				*mrealloc(void *ptr, size_t size);
int					free_all_malloc(void);
int					mfree(void **to_free);

#endif
