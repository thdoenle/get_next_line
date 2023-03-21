/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:20:30 by thdoenle          #+#    #+#             */
/*   Updated: 2022/11/28 16:49:08 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

int	gnl_clean_buf(t_buf *buf, void *ptr)
{
	if (ptr)
		free(ptr);
	if (buf->ptr)
		free(buf->ptr);
	buf->ptr = NULL;
	buf->size = 0;
	return (-1);
}
