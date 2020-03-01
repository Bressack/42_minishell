/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 13:36:27 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/29 15:40:30 by fredrikalindh    ###   ########.fr       */
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
void	*ft_memcpy(void *s1, const void *s2, size_t n);
char	*ft_strcpy(char *s1, const char *s2);
int		ft_strcmp(char *s1, char *s2);
char	*cat_value(char *s1, char *s2);
int		ft_isnum(char *str);
char	*ft_strdup(char *src);
int		ft_atoi(const char *str);
int		bi_error(char *ft, char *arg, char *mess, int f);
char	**ft_split(char *str, char *charset);
void	ft_bzero(void *s, int n);
#endif
