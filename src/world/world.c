/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:29:04 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/14 16:40:30 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

t_intersection	*intersect_world(t_world *world, t_ray ray)
{
	t_intersection	*xs;
	t_intersection	*aux;
	t_list			*objects;
	void			*next;

	xs = NULL;
	objects = world->objects;
	while (objects)
	{
		aux = intersect(objects->content, ray);
		while (aux)
		{
			next = aux->next;
			insert_intersection(&xs, aux);
			aux = next;
		}
		objects = objects->next;
	}
	return (xs);
}
