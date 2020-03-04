/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 13:36:27 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/04 18:36:25 by frlindh          ###   ########.fr       */
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
int		ft_strisnum(char *str);
char	*ft_strdup(char *src);
int		ft_atoi(const char *str);
int		bi_error(char *ft, char *arg, char *mess, int f);
char	**ft_split(char *str, char *charset);
void	ft_bzero(void *s, int n);
char	*ft_ctoa(unsigned int n);
int		is_letter(char c);
int		is_num(char c);
#endif
