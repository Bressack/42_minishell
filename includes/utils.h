/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 13:36:27 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/20 16:30:31 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <minishell.h>
char	*ft_strsub(char const *s, unsigned int start, size_t len);
char	*ft_strncpy(char *s1, const char *s2, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strlen(const char *s);
char	*ft_strjoin(int nb_str, ...);
char	*ft_strdup(char *src);
void	*ft_memcpy(void *s1, const void *s2, size_t n);
char	*ft_strcpy(char *s1, const char *s2);
#endif
