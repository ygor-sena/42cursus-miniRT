/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:46:00 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/09/06 12:05:05 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_chunk	*last_chunk(t_chunk *storage)
{
	if (!storage)
		return (NULL);
	while (storage->next)
		storage = storage->next;
	return (storage);
}

t_chunk	*get_node(t_chunk **storage)
{
	t_chunk	*node;

	node = last_chunk(*storage);
	if (has_newline(node))
		return (node);
	if (!node)
	{
		*storage = new_chunk();
		return (*storage);
	}
	node->next = new_chunk();
	return (node->next);
}

int	has_newline(t_chunk *node)
{
	int		index;

	if (!node)
		return (0);
	index = 0;
	while (node->text[index])
	{
		if (node->text[index++] == '\n')
		{
			node->newline = 1;
			break ;
		}
	}
	node->size = index;
	return (node->newline);
}

int	sum_chunks(t_chunk *storage)
{
	int		length;

	length = 0;
	while (storage)
	{
		length += storage->size;
		storage = storage->next;
	}
	return (length);
}

t_chunk	*new_chunk(void)
{
	t_chunk	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	new_node->newline = 0;
	new_node->size = 0;
	return (new_node);
}
