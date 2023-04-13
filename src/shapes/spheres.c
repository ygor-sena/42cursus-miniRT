/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spheres.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:30:21 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/11 14:58:00 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"

static t_hit_points	calculate_hit_points(t_sphere sphere, t_ray ray);

t_intersection	*intersect(t_sphere sphere, t_ray r)
{
	t_ray			ray;
	t_intersection	*xs;
	t_hit_points	c;

	ray = transform(r, inverse(sphere.transform));
	c = calculate_hit_points(sphere, ray);
	xs = NULL;
	if (c.delta < 0)
		return (NULL);
	insert_intersection(&xs, intersection(c.t1, sphere));
	insert_intersection(&xs, intersection(c.t2, sphere));
	return (xs);
}

void	set_transform(t_sphere *sphere, t_matrix transform)
{
	sphere->transform = transform;
}

static t_hit_points	calculate_hit_points(t_sphere sphere, t_ray ray)
{
	float		a;
	float		b;
	float		c;
	float		delta;
	t_vector	sphere_to_ray;

	sphere_to_ray = subtract(ray.origin, sphere.origin);
	a = dot(ray.direction, ray.direction);
	b = 2 * dot(ray.direction, sphere_to_ray);
	c = dot(sphere_to_ray, sphere_to_ray) - 1;
	delta = (b * b) - 4 * a * c;
	return ((t_hit_points){
		.t1 = (-b - sqrtf(delta)) / (2 * a),
		.t2 = (-b + sqrtf(delta)) / (2 * a),
		.delta = (b * b) - 4 * a * c,
	});
}

/**
 *	Hack, to ensure we have a clean vector, as due the inverse transpose 
 *	the w component could be affected if the transformation matrix included
 *	a translation.
 */
t_tuple	normal_at(t_sphere sphere, t_tuple world_point)
{
	t_tuple	object_point;
	t_tuple	object_normal;
	t_tuple	world_normal;

	object_point = multiply_tp_mx(inverse(sphere.transform), world_point);
	object_normal = subtract(object_point, point(0, 0, 0));
	world_normal = multiply_tp_mx(transpose(\
					inverse(sphere.transform)), object_normal);
	world_normal.w = 0.0;
	return (normalize(world_normal));
}
