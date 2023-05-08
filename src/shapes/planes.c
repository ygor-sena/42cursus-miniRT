/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:43:18 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/07 19:14:47 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"

t_shape	new_plane(void)
{
	t_shape	object;

	object = new_shape();
	object.normal_at = normal_at_plane;
	object.intersect = intersect_plane;
	return (object);
}

t_tuple	normal_at_plane(t_shape *shape, t_tuple world_point)
{
	(void) shape;
	(void) world_point;
	return (vector(0, 1, 0));
}

t_bool	intersect_plane(t_hit **xs, t_shape *shape, t_ray ray)
{
	float	t;

	if (fabsf(ray.direction.y) < EPSILON)
		return (FALSE);
	t = -ray.origin.y / ray.direction.y;
	insert_intersection(xs, intersection(t, shape));
	return (TRUE);
}
