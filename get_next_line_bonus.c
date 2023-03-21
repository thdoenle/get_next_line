/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:14:45 by thdoenle          #+#    #+#             */
/*   Updated: 2022/11/26 19:21:51 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	gnl_append_buffer(t_buf_lst *buf, char *tmp, ssize_t nb, t_buf_lst **lst)
{
	char	*new;
	ssize_t	i;

	if (buf->size > buf->size + nb)
		return (gnl_remove_buf(lst, buf));
	new = malloc(buf->size + nb);
	if (!new)
		return (gnl_remove_buf(lst, buf));
	i = 0;
	while (i < buf->size)
	{
		new[i] = (buf->ptr)[i];
		i++;
	}
	buf->size += nb;
	while (i < buf->size)
	{
		new[i] = *tmp;
		i++;
		tmp++;
	}
	if (buf->ptr)
		free(buf->ptr);
	buf->ptr = new;
	return (0);
}

int	gnl_read_until_eol(t_buf_lst *buf, t_buf_lst **lst)
{
	char	tmp[BUFFER_SIZE];
	ssize_t	nb;
	int		has_nl;

	nb = BUFFER_SIZE;
	has_nl = gnl_mem_hasnl(buf->ptr, buf->size);
	while (nb == BUFFER_SIZE && !has_nl)
	{
		nb = read(buf->fd, tmp, BUFFER_SIZE);
		if (nb == -1)
			return (gnl_remove_buf(lst, buf));
		has_nl = gnl_mem_hasnl(tmp, nb);
		if (nb && gnl_append_buffer(buf, tmp, nb, lst))
			return (-1);
	}
	return (0);
}

char	*gnl_dup_line_from_buffer(t_buf_lst *buf, ssize_t n, t_buf_lst **lst)
{
	char	*line;
	ssize_t	i;

	if (!n)
	{
		gnl_remove_buf(lst, buf);
		return (NULL);
	}
	line = malloc(n + 1);
	if (!line)
	{
		gnl_remove_buf(lst, buf);
		return (NULL);
	}
	i = 0;
	while (i < n)
	{
		line[i] = (buf->ptr)[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

int	gnl_remove_line_from_buffer(t_buf_lst *buf, ssize_t n, t_buf_lst **lst)
{
	char	*new;
	ssize_t	i;

	if (n >= buf->size)
	{
		gnl_remove_buf(lst, buf);
		return (0);
	}
	new = malloc(buf->size - n);
	if (!new)
		return (gnl_remove_buf(lst, buf));
	i = 0;
	while (i + n < buf->size)
	{
		new[i] = (buf->ptr)[i + n];
		i++;
	}
	buf->size -= n;
	free(buf->ptr);
	buf->ptr = new;
	return (0);
}

char	*get_next_line(int fd)
{
	static t_buf_lst	*lst = NULL;
	t_buf_lst			*buf;
	ssize_t				n;
	char				*line;

	buf = gnl_get_buf(&lst, fd);
	if (!buf)
		return (NULL);
	if (gnl_read_until_eol(buf, &lst))
		return (NULL);
	n = 0;
	while (n < buf->size && (buf->ptr)[n] != '\n')
		n++;
	if (n < buf->size)
		n++;
	line = gnl_dup_line_from_buffer(buf, n, &lst);
	if (!line)
		return (NULL);
	if (gnl_remove_line_from_buffer(buf, n, &lst))
	{
		free(line);
		return (NULL);
	}
	return (line);
}
