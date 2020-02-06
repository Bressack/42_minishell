/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 23:32:03 by tharchen          #+#    #+#             */
/*   Updated: 2020/01/31 01:53:00 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <ms.h>

typedef struct		s_split
{
	struct s_split	*next;
	struct s_split	*prev;
	char			*origine;
	char			*str;
	int				pos;
	int				len;
}		t_split;
int		ft_strcmp(char *s1, char *s2);
t_split	*strsplit(char *str, char *sep);
char	**ft_strsplit_array(char const *s, char c);
int		ft_strlen(const char *s);
int		ft_atoi(const char *str);
double	ft_atod(char *str);
char	ft_str_isdigit(char *s);
char	ft_str_isdouble(char *s);
char	ft_isdigit(char c);
int		ft_strstr(const char *haystack, const char *needle);
char	*ft_strndup(const char *src, long n);
char	*ft_strjoin(int nb_str, ...);
void	ft_bzero(void *s, int n);
int		ft_strfind(char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
#endif
