/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:42:38 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/09/06 12:05:09 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	read_line(int fd, t_chunk **storage);
void	fill_line(char **line, t_chunk *storage);
void	rewind_storage(t_chunk **storage);
t_chunk	*purge(t_chunk **storage);

char	*get_next_line(int fd)
{
	char			*line;
	static t_chunk	*storage[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	read_line(fd, &storage[fd]);
	fill_line(&line, storage[fd]);
	rewind_storage(&storage[fd]);
	return (line);
}

void	read_line(int fd, t_chunk **storage)
{
	t_chunk	*node;
	int		bytes_read;

	bytes_read = BUFFER_SIZE;
	while (bytes_read)
	{
		node = get_node(storage);
		if (node->newline)
			break ;
		bytes_read = read(fd, node->text, BUFFER_SIZE);
		if (bytes_read == GNL_EOF || bytes_read == GNL_ERR)
			return ;
		node->text[bytes_read] = '\0';
	}
}

void	fill_line(char **line, t_chunk *storage)
{
	int		tx_index;
	int		ln_index;
	int		length;

	length = sum_chunks(storage);
	if (!length)
		return ;
	*line = malloc(sizeof(**line) * (length + 1));
	if (!line)
		return ;
	ln_index = 0;
	while (storage)
	{
		tx_index = 0;
		while (ln_index < length && storage->text[tx_index])
			(*line)[ln_index++] = storage->text[tx_index++];
		storage->newline = 0;
		storage = storage->next;
	}
	(*line)[ln_index] = '\0';
}

void	rewind_storage(t_chunk **storage)
{
	int		begin;
	int		end;
	t_chunk	*last;

	last = purge(storage);
	if (!last)
		return ;
	begin = 0;
	end = last->size;
	while (last->text[end])
		last->text[begin++] = last->text[end++];
	last->text[begin] = '\0';
	(*storage)->size = begin;
}

t_chunk	*purge(t_chunk **storage)
{
	t_chunk	*node;

	if (*storage == NULL)
		return (NULL);
	while ((*storage)->next)
	{
		node = *storage;
		*storage = (*storage)->next;
		free(node);
	}
	if ((*storage)->size == 0)
	{
		free(*storage);
		*storage = NULL;
	}
	return (*storage);
}
