/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:36:20 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/14 13:35:30 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"

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

t_intersection	*intersection(float t, t_sphere *sphere)
{
	t_intersection	*hit;

	hit = oom(malloc(sizeof(t_intersection)));
	hit->t = t;
	hit->object.sphere = sphere;
	hit->next = NULL;
	return (hit);
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

void	erase_intersections(t_intersection **xs)
{
	t_intersection	*aux;

	aux = *xs;
	while (aux)
	{
		aux = aux->next;
		free(*xs);
		*xs = aux;
	}
	*xs = NULL;
}
