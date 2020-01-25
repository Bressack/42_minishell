/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsplit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 08:48:25 by tharchen          #+#    #+#             */
/*   Updated: 2020/01/09 15:20:12 by ssingevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ms.h>

static int			strsplit_strfind(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (-1);
}

static char			*strsplit_strsub(char *s, int start, int len)
{
	char	*new;
	int		i;

	new = try_malloc(sizeof(char) * (len + 1), _FL_);
	new[len] = '\0';
	i = -1;
	while (++i < len)
		new[i] = s[start + i];
	return (new);
}

static t_split		*str_bidule(char *str, char *sep, t_split *new)
{
	int				i[2];
	t_split			*begin_list;

	i[0] = 0;
	i[1] = 0;
	begin_list = NULL;
	while (str && str[i[0]])
	{
		if (str[i[0]] && strsplit_strfind(sep, str[i[0]]) == -1)
		{
			i[1] = i[0];
			while (str[i[1]] && strsplit_strfind(sep, str[i[1]]) == -1)
				i[1]++;
			new = try_malloc(sizeof(t_split), _FL_);
			new->origine = str;
			new->str = strsplit_strsub(str, i[0], i[1] - i[0]);
			new->pos = i[0] + 1;
			new->len = i[1] - i[0];
			ft_add_node_end_np((t_pnp **)&begin_list, (t_pnp *)new);
		}
		i[0] = i[1];
		while (str[i[0]] && strsplit_strfind(sep, str[i[0]]) != -1)
			i[0]++;
	}
	return (begin_list);
}

t_split				*strsplit(char *str, char *sep)
{
	t_split			*begin_list;
	t_split			*new;

	new = NULL;
	begin_list = str_bidule(str, sep, new);
	if (!begin_list)
	{
		new = try_malloc(sizeof(t_split), _FL_);
		new->origine = str;
		new->str = NULL;
		new->pos = 0;
		new->len = 0;
		ft_add_node_end_np((t_pnp **)&begin_list, (t_pnp *)new);
	}
	return (begin_list);
}
