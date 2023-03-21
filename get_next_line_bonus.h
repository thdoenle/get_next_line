/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:12:49 by thdoenle          #+#    #+#             */
/*   Updated: 2022/11/26 19:09:37 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_buf_lst
{
	char				*ptr;
	ssize_t				size;
	int					fd;
	struct s_buf_lst	*next;
}	t_buf_lst;

char		*get_next_line(int fd);
int			gnl_mem_hasnl(char *s, ssize_t n);
t_buf_lst	*gnl_get_buf(t_buf_lst **lst, int fd);
int			gnl_remove_buf(t_buf_lst **lst, t_buf_lst *buf);

#endif
