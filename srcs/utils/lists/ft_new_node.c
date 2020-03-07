/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 13:06:52 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/07 08:10:06 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <double_linked.h>

void		*ft_new_node(
	size_t size, void (*f)(void *, int, va_list), int nb_arg, ...)
{
	va_list	ap;
	void	*new;

	new = mmalloc(size);
	va_start(ap, nb_arg);
	f(new, nb_arg, ap);
	va_end(ap);
	return (new);
}
