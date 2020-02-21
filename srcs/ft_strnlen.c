/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 12:08:42 by frlindh           #+#    #+#             */
/*   Updated: 2020/02/21 13:44:31 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>

int		ft_strnlen(char *str, int n)
{
	int	i;

	i = 0;
	if (n != -1)
		while (str && str[i] && i < n)
			i++;
	else
		while (str && str[i])
			i++;
	return (i);
}
