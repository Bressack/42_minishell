/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 13:22:21 by tharchen          #+#    #+#             */
/*   Updated: 2020/01/20 13:27:31 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ms.h>

t_split_exp			split_exp(char *str, char **sep)
{
	int				i;
	int				j;
	int				k;

	i = -1;
	while (str[++i])
	{
		j = -1;
		while (sep[++j])
		{
			k = -1;
			while (sep[j][++k])
			{
				if (!sep[j][k])
					
				if (str[i] != sep[j][k])
					break ;
			}
		}
	}
}
