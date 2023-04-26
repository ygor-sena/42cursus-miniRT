/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:22:34 by yde-goes          #+#    #+#             */
/*   Updated: 2023/04/25 18:34:09 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

t_bool	is_shadowed(t_world *world, t_tuple point)
{
	t_tuple			v;
	t_ray			r;
	t_intersection	*intersections;
	t_intersection	*h;

	v = subtract(world->lights->position, point);
	r = new_ray(point, normalize(v));
	intersections = intersect_world(world, r);
	h = hit(intersections);
	if (h && (h->t < magnitude(v)))
		return (TRUE);
	return (FALSE);
}
