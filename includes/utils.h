/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 13:36:27 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/15 13:47:35 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <minishell.h>
int		ft_strlen(const char *s);
char	*ft_strsub(char const *s, unsigned int start, size_t len);
char	*ft_strncpy(char *s1, const char *s2, size_t n);
#endif