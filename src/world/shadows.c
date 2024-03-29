/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:22:34 by yde-goes          #+#    #+#             */
/*   Updated: 2023/05/24 08:38:06 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

t_bool	is_shadowed(t_world *world, t_tuple point, int index)
{
	t_tuple	v;
	t_ray	r;
	t_hit	*intersections;
	t_hit	*h;

	v = subtract(world->lights[index].position, point);
	r = new_ray(point, normalize(v));
	intersections = intersect_world(world, r);
	h = hit(intersections);
	if (h && (h->t < magnitude(v)))
		return (TRUE);
	return (FALSE);
}
