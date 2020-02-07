/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 13:06:52 by tharchen          #+#    #+#             */
/*   Updated: 2019/11/27 16:36:23 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ms.h>

void		*ft_new_node(
	size_t size, void (*f)(void *, int, va_list), int nb_arg, ...)
{
	va_list	ap;
	void	*new;

	if (!(new = try_malloc(size, _FL_)))
		return (NULL);
	va_start(ap, nb_arg);
	f(new, nb_arg, ap);
	va_end(ap);
	return (new);
}
