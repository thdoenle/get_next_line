/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:12:49 by thdoenle          #+#    #+#             */
/*   Updated: 2022/11/28 16:48:43 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_buf
{
	char	*ptr;
	ssize_t	size;
}	t_buf;

char	*get_next_line(int fd);
int		gnl_mem_hasnl(char *s, ssize_t n);
int		gnl_clean_buf(t_buf *buf, void *ptr);

#endif
