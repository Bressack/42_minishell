/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iss.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 14:59:39 by tharchen          #+#    #+#             */
/*   Updated: 2020/01/30 16:04:00 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ms.h>

int					ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\r' ||
			c == '\v' || c == '\f' || c == ' ');
}

int					ft_isquote(char c)
{
	return (c == '\"' || c == '\'');
}

#ifdef BONUS

int					ft_isspecial(char *s)
{
	return ((*s == ';') ||
			(*s == '&' && *(s + 1) == '&') ||
			(*s == '|' && *(s + 1) == '|') ||
			(*s == '|') ||
			(*s == '&'));
}

#else

int					ft_isspecial(char *s)
{
	return ((*s == ';') ||
			(*s == '|'));
}

#endif
