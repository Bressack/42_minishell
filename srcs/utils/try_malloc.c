/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_malloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchen <tarchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 12:09:53 by tarchen           #+#    #+#             */
/*   Updated: 2020/02/27 17:38:14 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// void		*try_malloc(size_t size, char *f, int l)
// {
// 	void	*alloc;
//
// 	if (!(alloc = malloc(size)))
// 	{
// 		(void)f;
// 		(void)l;
// 		// dprintf(2, "error: malloc can't allocate region in: "C_G_RED"%s"C_RES
// 			// " - (line:"C_G_MAGENTA"%d"C_RES"\n", f, l);
// 		exit(-1);
// 	}
// 	return (alloc);
// }
//
// void		try_free_(void **p, char *f, int l)
// {
// 	(void)f;
// 	(void)l;
// 	if (*p)
// 	{
// 		free(*p);
// 		*p = NULL;
// 	}
// }

/* ************************************************************************** */

t_debug_malloc	g_debug_malloc[__SIZE_MALLOC_DEBUG];
size_t			g_i_malloc = 1;

typedef struct		s_mmopt
{
	int				t;
	char			*s;
}					t_mmopt;

t_mmopt				g_mmoptt[5] =
{
	{PRINT_ALL, "PRINT_ALL"},
	{PRINT_ERR, "PRINT_ERR"},
	{PRINT_DBLFREE, "PRINT_DBLFREE"},
	{PRINT_NULLFREE, "PRINT_NULLFREE"},
	{PRINT_OK, "PRINT_OK"}
};

void		print_mem__(int opt)
{
	int		total_node_leaked = 0;
	int		total_mem_leaked = 0;
	int		total_mem_leaked_true = 0;
	int		total_mem_alloc = 0;
	int		total_mem_alloc_true = 0;
	size_t	i;

	printf(""C_G_RED"malloc:"C_RES" "C_G_WHITE"display debug array"C_RES"\n"C_G_RED"tracking:"C_RES" "C_G_WHITE"%s"C_RES"\n", g_mmoptt[opt].s);
	dprintf(2, " %s         || %s                                                || %s                                       || %s\n", C_G_RED"ADDRESS"C_RES, C_G_CYAN"MALLOC"C_RES, C_G_MAGENTA"FREE"C_RES, C_G_YELLOW"MARK"C_RES);
	dprintf(2, "                 || %s             | %s   | %s      | %s || %s             | %s   | %s ||\n", "function", "line", "size", "real size", "function", "line", "count free");
	dprintf(2, "-------------------------------------------------------------------------------------------------------------------------------\n");
	for (i = 0; i < g_i_malloc; i++)
	{
			 if (opt == PRINT_ERR      && !GDM.f_malloc && GDM.nb_free == 1)
			continue ;
		else if (opt == PRINT_DBLFREE  && GDM.nb_free <= 1)
			continue ;
		else if (opt == PRINT_NULLFREE && !GDM.f_malloc && GDM.nb_free == 1)
			continue ;
		else if (opt == PRINT_OK       && !GDM.f_malloc && GDM.nb_free == 1)
			continue ;

		dprintf(2, " %-15p || %-20.20s | %-6d | %-9d | %-9d || %-20.20s | %-6d | %-2d         || %s"C_RES"\n",
			GDM.mem,
			i ? GDM.f_malloc : "(null pointer)",
			i ? GDM.l_malloc : 0,
			i ? GDM.size : 0,
			i ? GDM.real_size : 0,
			GDM.nb_free >= 1 ? GDM.f_free : "---------------------------------",
			GDM.nb_free >= 1 ? GDM.l_free : 0,
			GDM.nb_free,
			!GDM.mem && GDM.nb_free == 1 ? C_G_GREEN"OK" : C_G_RED"KO" // maybe ||
		);
		!i ? dprintf(2, "-------------------------------------------------------------------------------------------------------------------------------\n") : 0;
		if (GDM.f_malloc && !GDM.nb_free)
		{
			total_node_leaked++;
			total_mem_leaked += GDM.size;
			total_mem_leaked_true += GDM.real_size;
		}
		total_mem_alloc += GDM.size;
		total_mem_alloc_true += GDM.real_size;
	}
	dprintf(2, "%d leaks for %zu total node(s)\n", total_node_leaked, i);
	dprintf(2, "%d (%d) bytes lost for a %d (%d) total bytes or simply %.2f%% (%.2f%%)\n", total_mem_leaked, total_mem_leaked_true, total_mem_alloc, total_mem_alloc_true, (double)((double)((double)total_mem_leaked * 100) / (double)total_mem_alloc), (double)((double)((double)total_mem_leaked_true * 100) / (double)total_mem_alloc_true));
	dprintf(2, "%lu bytes used by debug\n", MEM_USED_BY_DEBUG);
}

void		*try_malloc(size_t size, char *f, int l)
{
	void	*alloc;

	if (g_i_malloc == __SIZE_MALLOC_DEBUG)
	{
		dprintf(2, C_G_RED"error:"C_G_WHITE" not enough space on malloc debug array. (actually %d)\n", __SIZE_MALLOC_DEBUG);
		print_mem__(PRINT_ALL);
		exit(-2);
	}
	if (!(alloc = malloc(size)))
	{
		dprintf(2, C_G_RED"error:"C_G_WHITE" malloc can't allocate region in: "C_G_RED"%s"C_WHITE
			" - (line:"C_G_MAGENTA"%d"C_RES")\n", f, l);
		print_mem__(PRINT_ALL);
		exit(-1);
	}
	ft_bzero(alloc, size);
	g_debug_malloc[g_i_malloc].f_free = 0;
	g_debug_malloc[g_i_malloc].l_free = 0;
	g_debug_malloc[g_i_malloc].nb_free = 0;
	g_debug_malloc[g_i_malloc].mem = alloc;
	g_debug_malloc[g_i_malloc].f_malloc = f;
	g_debug_malloc[g_i_malloc].l_malloc = l;
	g_debug_malloc[g_i_malloc].size = (int)size;
	g_debug_malloc[g_i_malloc].real_size = (int)(size + (16 - size % 16));
	g_i_malloc++;
	return (alloc);
}

void		try_free_(void **p, char *f, int l)
{
	int		i;

	if (!p)
		return ;
	i = -1;
	while (++i < __SIZE_MALLOC_DEBUG && *p)
		if (g_debug_malloc[i].mem == *p && !g_debug_malloc[i].nb_free)
			break ;
	if (i >= __SIZE_MALLOC_DEBUG)
	{
		for (i = 0; i < __SIZE_MALLOC_DEBUG; i++)
			if (g_debug_malloc[i].mem == *p)
				break ;
	}
	if (i < __SIZE_MALLOC_DEBUG)
	{
		if (*p && !g_debug_malloc[i].nb_free)
		{
			free(*p);
			*p = NULL;
			g_debug_malloc[i].f_free = f;
			g_debug_malloc[i].l_free = l;
		}
		g_debug_malloc[i].nb_free++;
	}
}

void		try_free_all(char *f, int l)
{
	for (int i = 0; i < __SIZE_MALLOC_DEBUG; i++)
	{
		if (g_debug_malloc[i].mem && !g_debug_malloc[i].nb_free)
		{
			try_free_(&g_debug_malloc[i].mem, _FL_);
			g_debug_malloc[i].f_free = f;
			g_debug_malloc[i].l_free = l;
			g_debug_malloc[i].nb_free++;
		}
	}
}
