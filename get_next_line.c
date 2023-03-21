/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thdoenle <thdoenle@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:14:45 by thdoenle          #+#    #+#             */
/*   Updated: 2022/11/28 16:54:33 by thdoenle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_append_buffer(t_buf *buf, char *tmp, ssize_t nb)
{
	char	*new;
	ssize_t	i;

	if (buf->size > buf->size + nb)
		return (gnl_clean_buf(buf, tmp));
	new = malloc(buf->size + nb);
	if (!new)
		return (gnl_clean_buf(buf, tmp));
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

int	gnl_read_until_eol(t_buf *buf, int fd)
{
	char	*tmp;
	ssize_t	nb;
	int		has_nl;

	tmp = malloc(BUFFER_SIZE);
	if (!tmp)
		return (gnl_clean_buf(buf, NULL));
	nb = BUFFER_SIZE;
	has_nl = gnl_mem_hasnl(buf->ptr, buf->size);
	while (nb > 0 && !has_nl)
	{
		nb = read(fd, tmp, BUFFER_SIZE);
		if (nb == -1)
			return (gnl_clean_buf(buf, tmp));
		has_nl = gnl_mem_hasnl(tmp, nb);
		if (nb && gnl_append_buffer(buf, tmp, nb))
			return (-1);
	}
	free(tmp);
	return (0);
}

char	*gnl_dup_line_from_buffer(t_buf *buf, ssize_t n)
{
	char	*line;
	ssize_t	i;

	if (!n)
		return (NULL);
	line = malloc(n + 1);
	if (!line)
	{
		gnl_clean_buf(buf, NULL);
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

int	gnl_remove_line_from_buffer(t_buf *buf, ssize_t n, char *line)
{
	char	*new;
	ssize_t	i;

	if (n >= buf->size)
	{
		gnl_clean_buf(buf, NULL);
		return (0);
	}
	new = malloc(buf->size - n);
	if (!new)
		return (gnl_clean_buf(buf, line));
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
	static t_buf	buf = {NULL, 0};
	ssize_t			n;
	char			*line;

	if (gnl_read_until_eol(&buf, fd))
		return (NULL);
	n = 0;
	while (n < buf.size && (buf.ptr)[n] != '\n')
		n++;
	if (n < buf.size)
		n++;
	line = gnl_dup_line_from_buffer(&buf, n);
	if (gnl_remove_line_from_buffer(&buf, n, line))
		return (NULL);
	return (line);
}
