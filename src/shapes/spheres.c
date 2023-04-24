/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spheres.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:30:21 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/23 12:03:08 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"

static t_distance	calculate_distance(t_sphere *sphere, t_ray ray);

t_sphere	*new_sphere(void)
{
	t_sphere	*s;

	s = oom(malloc(sizeof(t_sphere)));
	s->origin = point(0, 0, 0);
	s->radius = 1.0;
	s->transform = get_identity_matrix();
	s->material = material();
	return (s);
}

t_intersection	*intersect(t_sphere *sphere, t_ray r)
{
	t_ray			ray;
	t_intersection	*xs;
	t_distance		d;

	ray = transform(r, inverse(sphere->transform));
	d = calculate_distance(sphere, ray);
	xs = NULL;
	if (d.determinant < 0)
		return (NULL);
	insert_intersection(&xs, intersection(d.t1, sphere));
	insert_intersection(&xs, intersection(d.t2, sphere));
	return (xs);
}

void	set_transform(t_sphere *sphere, t_matrix transform)
{
	sphere->transform = transform;
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
		.t1 = (-b - sqrtf(delta)) / (2 * a),
		.t2 = (-b + sqrtf(delta)) / (2 * a),
		.determinant = (b * b) - 4 * a * c,
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
	world_normal = multiply_tp_mx(transpose(
				inverse(sphere.transform)), object_normal);
	world_normal.w = 0.0;
	return (normalize(world_normal));
}
