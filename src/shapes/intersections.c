/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:36:20 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/25 22:43:58 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"

#define NODE_MAX 32

t_intersection	*intersection(float t, t_shape *shape)
{
	static t_intersection	pool[NODE_MAX];
	static size_t			node;
	t_intersection			*hit;

	hit = pool + (node++ % NODE_MAX);
	hit->t = t;
	hit->object = shape;
	hit->next = NULL;
	return (hit);
}

void	insert_intersection(t_intersection **xs, t_intersection *isect)
{
	t_intersection	*prev;
	t_intersection	*curr;

	prev = NULL;
	curr = *xs;
	while (curr && curr->t < isect->t)
	{
		prev = curr;
		curr = curr->next;
	}
	if (prev == NULL)
	{
		isect->next = *xs;
		*xs = isect;
		return ;
	}
	prev->next = isect;
	isect->next = curr;
}

// TODO: rename to nearest_hit
t_intersection	*hit(t_intersection *xs)
{
	while (xs != NULL && xs->t < 0)
		xs = xs->next;
	return (xs);
}

int	intersection_count(t_intersection *xs)
{
	int	count;

	count = 0;
	while (xs)
	{
		xs = xs->next;
		count++;
	}
	return (count);
}
