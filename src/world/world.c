/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:29:04 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/12 10:50:09 by yde-goes         ###   ########.fr       */
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
	comps.sight.normalv = comps.object->normal_at(comps.object, comps.point);
	if (dot(comps.sight.normalv, comps.sight.eyev) < 0)
	{
		comps.inside = TRUE;
		comps.sight.normalv = negate(comps.sight.normalv);
		comps.over_point = add(
				comps.point, multiply(comps.sight.normalv, EPSILON));
		return (comps);
	}
	comps.over_point = add(comps.point, multiply(comps.sight.normalv, EPSILON));
	comps.reflectv = reflect(ray.direction, comps.sight.normalv);
	comps.inside = FALSE;
	return (comps);
}

t_color	shade_hit(t_world world, t_comps comps, size_t remaining)
{
	t_color	surface;
	t_color	reflected;

	world.lights->in_shadow = is_shadowed(&world, comps.over_point);
	surface = lighting(comps.object->material,
			world.lights[0], comps.point, comps.sight);
	reflected = reflected_color(world, comps, remaining);
	return (add_color(surface, reflected));
}

t_color	color_at(t_world world, t_ray ray, size_t remaining)
{
	t_hit	*x;
	t_comps	comps;
	t_color	color;

	intersect_world(&world, ray);
	x = hit(world.xs);
	if (x == NULL)
		return (new_color(0, 0, 0));
	comps = prepare_computations(x, ray);
	color = shade_hit(world, comps, remaining);
	return (color);
}

t_color	reflected_color(t_world world, t_comps comps, size_t remaining)
{
	t_ray	reflect_ray;
	t_color	color;

	if (!remaining || !comps.object->material.reflective)
		return (new_color(0, 0, 0));
	reflect_ray = new_ray(comps.over_point, comps.reflectv);
	color = color_at(world, reflect_ray, remaining - 1);
	return (multiply_color(color, comps.object->material.reflective));
}
