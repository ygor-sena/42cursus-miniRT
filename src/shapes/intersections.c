/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:36:20 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/25 11:40:54 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"

#define NODE_MAX 32

t_intersection	*intersection(float t, t_sphere *sphere)
{
	static t_intersection	pool[NODE_MAX];
	static size_t			node;
	t_intersection			*hit;

	hit = pool + (node++ % NODE_MAX);
	hit->t = t;
	hit->object.sphere = sphere;
	hit->next = NULL;
	return (hit);
}

void	insert_intersection(t_intersection **xs, t_intersection *isect)
{
	t_intersection	*aux;

	if (*xs == NULL || isect->t < (*xs)->t)
	{
		isect->next = *xs;
		*xs = isect;
		return ;
	}
	aux = *xs;
	while (aux->next && aux->next->t < isect->t)
		aux = aux->next;
	isect->next = aux->next;
	aux->next = isect;
}

t_intersection	*hit(t_intersection *xs)
{
	while (xs)
	{
		if (xs->t >= 0)
			return (xs);
		xs = xs->next;
	}
	return (NULL);
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
