/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 20:35:31 by frlindh           #+#    #+#             */
/*   Updated: 2020/03/03 22:10:28 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_ctoa(unsigned int n)
{
	char	*num;
	int		i;
	int		div;

	num = (char *)mmalloc(5);
	i = 0;
	div = 1000;
	while (n / div == 0 && div > 1)
		div = div / 10;
	while (div >= 1)
	{
		num[i++] = n / div + '0';
		n = n % div;
		div = div / 10;
	}
	num[i] = '\0';
	return (num);
}
