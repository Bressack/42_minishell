/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 09:07:42 by tharchen          #+#    #+#             */
/*   Updated: 2020/01/30 13:46:34 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define GNL_RET 0
# define GNL_LEN 1
# define GNL_BUFFER_SIZE	1024
# define CURR 0
# define SAVE 1
# include <ms.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include <libc.h>

int		get_next_line(const int fd, char **line);
#endif
