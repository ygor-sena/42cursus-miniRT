/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:29:04 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/24 19:47:36 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

// PERF: add a static list to keep all memory allocated
t_intersection	*intersect_world(t_world *world, t_ray ray)
{
	t_intersection	*xs;
	t_intersection	*aux;
	t_shape			*objects;
	void			*next;
	int				n;

	n = 0;
	xs = NULL;
	objects = world->objects;
	while (n < world->object_count)
	{
		aux = intersect(&objects[n].sphere, ray);
		while (aux)
		{
			next = aux->next;
			insert_intersection(&xs, aux);
			aux = next;
		}
		n++;
	}
	return (xs);
}

t_comps	prepare_computations(t_intersection *intersection, t_ray ray)
{
	t_comps	comps;

	comps.t = intersection->t;
	comps.object = intersection->object;
	comps.point = position(ray, comps.t);
	comps.sight.eyev = negate(ray.direction);
	comps.sight.normalv = normal_at(*comps.object.sphere, comps.point);
	if (dot(comps.sight.normalv, comps.sight.eyev) < 0)
	{
		comps.inside = TRUE;
		comps.sight.normalv = negate(comps.sight.normalv);
		return (comps);
	}
	comps.inside = FALSE;
	return (comps);
}

t_color	shade_hit(t_world world, t_comps comps)
{
	return (
		lighting(
			comps.object.sphere->material,
			*(t_light *)world.lights->content,
			comps.point,
			comps.sight
		));
}

t_color	color_at(t_world world, t_ray ray)
{
	t_intersection	*xs;
	t_intersection	*x;
	t_comps			comps;
	t_color			color;

	xs = intersect_world(&world, ray);
	x = hit(xs);
	if (x == NULL)
	{
		erase_intersections(&xs);
		return (new_color(0, 0, 0));
	}
	comps = prepare_computations(x, ray);
	color = shade_hit(world, comps);
	erase_intersections(&xs);
	return (color);
}
