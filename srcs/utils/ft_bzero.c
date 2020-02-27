/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:30:38 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/27 17:38:11 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_bzero(void *s, int n)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (n > 0)
	{
		n--;
		str[n] = '\0';
	}
}
