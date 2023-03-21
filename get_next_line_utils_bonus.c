/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:20:30 by thdoenle          #+#    #+#             */
/*   Updated: 2022/11/26 19:24:48 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	gnl_mem_hasnl(char *s, ssize_t n)
{
	while (n)
	{
		if (*s == '\n')
			return (1);
		s++;
		n--;
	}
	return (0);
}

int	gnl_remove_buf(t_buf_lst **lst, t_buf_lst *buf)
{
	t_buf_lst	**buf_ptr;
	t_buf_lst	*next;

	buf_ptr = lst;
	while (*buf_ptr != buf)
		buf_ptr = &((*buf_ptr)->next);
	next = (*buf_ptr)->next;
	if ((*buf_ptr)->ptr)
		free((*buf_ptr)->ptr);
	free(*buf_ptr);
	*buf_ptr = next;
	return (-1);
}

t_buf_lst	*gnl_get_buf(t_buf_lst **lst, int fd)
{
	t_buf_lst	**buf;

	buf = lst;
	while (*buf)
	{
		if ((*buf)->fd == fd)
			return (*buf);
		buf = &((*buf)->next);
	}
	*buf = malloc(sizeof(**buf));
	if (!*buf)
		return (NULL);
	(*buf)->ptr = NULL;
	(*buf)->size = 0;
	(*buf)->fd = fd;
	(*buf)->next = NULL;
	return (*buf);
}
