/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:36:20 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/05 20:49:56 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "spheres.h"
#include "matrices.h"

void	insert_intersection(t_intersection **xs, t_intersection *i)
{
	t_intersection	*aux;

	if (*xs == NULL || i->t < (*xs)->t)
	{
		i->next = *xs;
		*xs = i;
		return ;
	}
	aux = *xs;
	while (aux->next && aux->next->t < i->t)
		aux = aux->next;
	i->next = aux->next;
	aux->next = i;
}

t_intersection	*intersection(float t, t_sphere sphere)
{
	t_intersection	*i;

	i = malloc(sizeof(t_intersection));
	if (i == NULL)
		return (NULL);
	i->t = t;
	i->object.sphere = sphere;
	i->next = NULL;
	return (i);
}

t_intersection	*hit(t_intersection *xs)
{
	t_intersection	*aux;

	aux = xs;
	while (aux)
	{
		if (aux->t >= 0)
			return (aux);
		aux = aux->next;
	}
	return (NULL);
}

void	intersections_free(t_intersection **xs)
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
