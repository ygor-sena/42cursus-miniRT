/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spheres.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:30:21 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/26 09:50:51 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"

static t_distance	calculate_distance(t_sphere *sphere, t_ray ray);

t_shape	new_sphere(void)
{
	t_shape	object;

	object = new_shape();
	object.sphere.origin = point(0, 0, 0);
	object.sphere.radius = 1.0;
	object.normal_at = normal_at_sphere;
	object.intersect = intersect_sphere;
	object.material.diffuse = 0.7;
	object.material.specular = 0.3;
	return (object);
}

t_bool	intersect_sphere(t_hit **xs, t_shape *shape, t_ray ray)
{
	t_distance	d;

	d = calculate_distance(&shape->sphere, ray);
	if (d.determinant < 0)
		return (FALSE);
	insert_intersection(xs, intersection(d.t1, shape));
	insert_intersection(xs, intersection(d.t2, shape));
	return (TRUE);
}

static t_distance	calculate_distance(t_sphere *sphere, t_ray ray)
{
	float		a;
	float		b;
	float		c;
	float		delta;
	t_vector	sphere_to_ray;

	sphere_to_ray = subtract(ray.origin, sphere->origin);
	a = dot(ray.direction, ray.direction);
	b = 2 * dot(ray.direction, sphere_to_ray);
	c = dot(sphere_to_ray, sphere_to_ray) - 1;
	delta = (b * b) - 4 * a * c;
	return ((t_distance){
		.a = a,
		.b = b,
		.c = c,
		.t1 = (-b - sqrtf(delta)) / (2 * a),
		.t2 = (-b + sqrtf(delta)) / (2 * a),
		.determinant = delta,
	});
}

t_vector	normal_at_sphere(t_shape *shape, t_point object_point)
{
	t_vector	object_normal;

	(void) shape;
	object_normal = subtract(object_point, point(0, 0, 0));
	object_normal.w = 0.0;
	return (normalize(object_normal));
}
/**
 * HACK: to ensure we have a clean vector, as due the inverse transpose
 * the w component could be affected if the transformation matrix included
 * a translation.
 */
