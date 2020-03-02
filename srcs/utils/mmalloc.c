/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 18:34:17 by frlindh           #+#    #+#             */
/*   Updated: 2020/03/02 18:29:03 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_list	*g_all_malloc;

void	*mmalloc(unsigned int size)
{
	void	*new;
	t_list	*list;

	if (!(new = malloc(size)))
	{
		free_all_malloc();
		ft_dprintf(2, "allocation error");
		exit (1);
	}
	if (!(list = (t_list *)malloc(sizeof(t_list))))
	{
		free_all_malloc();
		ft_dprintf(2, "allocation error");
		exit (1);
	}
	ft_bzero(new, size);
	// ft_bzero(list, sizeof(t_list));
	list->data = new;
	list->next = g_all_malloc;
	g_all_malloc = list;
	return (new);
}

void	*mrealloc(void *ptr, size_t size)
{
	t_list	*list;

	list = g_all_malloc;
	while (ptr && list && list->data != ptr)
		list = list->next;
	if (ptr && list)
	{
		ptr = realloc(ptr, size);
		list->data = ptr;
	}
	else if (ptr)
	{
		ptr = realloc(ptr, size);
		if (!(list = (t_list *)malloc(sizeof(t_list))))
		{
			free_all_malloc();
			ft_dprintf(2, "allocation error");
			exit (1);
		}
		list->data = ptr;
		list->next = g_all_malloc;
		g_all_malloc = list;
	}
	else
		ptr = mmalloc(size);
	return (ptr);
}

int		free_all_malloc(void)
{
	t_list *prev;

	while (g_all_malloc)
	{
		free(g_all_malloc->data);
		prev = g_all_malloc;
		g_all_malloc = g_all_malloc->next;
		free(prev);
	}
	return (0);
}

void	mfree(void *to_free)
{
	t_list **indir;
	t_list *f;

	indir = &g_all_malloc;
	while (*indir && (*indir)->data != to_free)
		indir = &((*indir)->next);
	f = *indir;
	if (f)
		*indir = f->next;
	free(f->data);
	free(f);
}
