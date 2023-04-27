/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:29:04 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/27 16:58:13 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

t_hit	*intersect_world(t_world *world, t_ray ray)
{
	int		n;
	t_shape	*objects;

	n = 0;
	world->xs = NULL;
	objects = world->objects;
	while (n < world->object_count)
	{
		intersect(&world->xs, objects + n, ray);
		n++;
	}
	return (world->xs);
}

t_comps	prepare_computations(t_hit *intersection, t_ray ray)
{
	t_comps	comps;

	comps.t = intersection->t;
	comps.object = intersection->object;
	comps.point = position(ray, comps.t);
	comps.sight.eyev = negate(ray.direction);
	comps.sight.normalv = normal_at(comps.object, comps.point);
	if (dot(comps.sight.normalv, comps.sight.eyev) < 0)
	{
		comps.inside = TRUE;
		comps.sight.normalv = negate(comps.sight.normalv);
		comps.over_point = add(
				comps.point, multiply(comps.sight.normalv, EPSILON));
		return (comps);
	}
	comps.over_point = add(comps.point, multiply(comps.sight.normalv, EPSILON));
	comps.inside = FALSE;
	return (comps);
}

t_color	shade_hit(t_world world, t_comps comps)
{
	world.lights->in_shadow = is_shadowed(&world, comps.over_point);
	return (
		lighting(
			comps.object->material,
			world.lights[0],
			comps.point,
			comps.sight
		));
}

t_color	color_at(t_world world, t_ray ray)
{
	t_hit	*x;
	t_comps	comps;
	t_color	color;

	intersect_world(&world, ray);
	x = hit(world.xs);
	if (x == NULL)
		return (new_color(0, 0, 0));
	comps = prepare_computations(x, ray);
	color = shade_hit(world, comps);
	return (color);
}
