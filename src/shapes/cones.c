/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cones.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:56:52 by yde-goes          #+#    #+#             */
/*   Updated: 2023/05/22 11:16:52 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"

static t_distance	calculate_distance(t_ray ray);
static void			intersect_caps(t_hit **xs, t_shape *shape, t_ray ray);
//static t_bool		check_cap(t_ray ray, float t, float cone_range);

t_shape	new_cone(void)
{
	t_shape	object;

	object = new_shape();
	object.cone.origin = point(0, 0, 0);
	object.cone.minimum = -INFINITY;
	object.cone.maximum = INFINITY;
	object.cone.closed = FALSE;
	object.normal_at = normal_at_cone;
	object.intersect = intersect_cone;
	return (object);
}

t_tuple	normal_at_cone(t_shape *shape, t_tuple world_point)
{
	float	dist;
	float	min_radius;
	float	max_radius;
	float	y;

	dist = powf(world_point.x, 2) + powf(world_point.z, 2);
	max_radius = powf(shape->cone.maximum, 2);
	if (dist < max_radius && world_point.y >= shape->cone.maximum - EPSILON)
		return (vector(0, 1, 0));
	min_radius = powf(shape->cone.minimum, 2);
	if (dist < min_radius && world_point.y <= shape->cone.minimum + EPSILON)
		return (vector(0, -1, 0));
	y = sqrtf(dist);
	if (world_point.y > 0.0)
		y = -y;
	return (vector(world_point.x, y, world_point.z));
}

/* t_bool	intersect_cone(t_hit **xs, t_shape *shape, t_ray ray)
{
	t_distance	d;
	//float		t;
	float		y0;
	float		y1;

	d = calculate_distance(ray);
	if (fabsf(d.a) < EPSILON && fabsf(d.b) < EPSILON)
		return (FALSE);
	if (fabsf(d.a) < EPSILON)
	{
		//t = (-d.c) / (d.b * 2);
		//insert_intersection(xs, intersection(t, shape));
	}
	else
	{
		if (d.determinant < 0)
			return (FALSE);
		if (d.t1 > d.t2)
			swap(&d.t1, &d.t2);
		y0 = ray.origin.y + (d.t1 * ray.direction.y);
		y1 = ray.origin.y + (d.t2 * ray.direction.y);
		if (shape->cone.minimum < y0 && y0 < shape->cone.maximum)
			insert_intersection(xs, intersection(d.t1, shape));
		if (shape->cone.minimum < y1 && y1 < shape->cone.maximum)
			insert_intersection(xs, intersection(d.t2, shape));
	}
	intersect_caps(xs, shape, ray);
	return (TRUE);
} */




/* if (is_epsilon_zero(d.a, 0.0))
{
	if (is_epsilon_zero(d.b, 0.0))
		return (FALSE);
	insert_intersection(xs, intersection((-d.c) / (2 * d.b), shape));
	return (TRUE);
} */
t_bool	intersect_cone(t_hit **xs, t_shape *shape, t_ray ray)
{
	t_distance	d;
	float		y0;
	float		y1;

	intersect_caps(xs, shape, ray);
	d = calculate_distance(ray);
	// ray is parallel to the y axis
	// ray does not intersect the cylinder
	if (fabsf(d.a) < EPSILON)
	{
		// ray misses both halves of cone
		if (fabsf(d.b) < EPSILON)
			return (FALSE);
		// there's one intersection point
		insert_intersection(xs, intersection((-d.c) / (2 * d.b), shape));
		return (TRUE);
	}
	// ray does not intersect cone
	if (d.determinant < 0)
		return (FALSE);
	if (d.t1 > d.t2)
		swap(&d.t1, &d.t2);
	y0 = ray.origin.y + d.t1 * ray.direction.y;
	y1 = ray.origin.y + d.t2 * ray.direction.y;
	if (shape->cone.minimum < y0 && y0 < shape->cone.maximum)
		insert_intersection(xs, intersection(d.t1, shape));
	if (shape->cone.minimum < y1 && y1 < shape->cone.maximum)
		insert_intersection(xs, intersection(d.t2, shape));
	return (TRUE);
}

static t_distance	calculate_distance(t_ray ray)
{
	float	a;
	float	b;
	float	c;
	float	discriminant;

	a = (powf(ray.direction.x, 2) - powf(ray.direction.y, 2)
			+ powf(ray.direction.z, 2));
	b = (2 * ray.origin.x * ray.direction.x)
		- (2 * ray.origin.y * ray.direction.y)
		+ (2 * ray.origin.z * ray.direction.z);
	c = powf(ray.origin.x, 2) - powf(ray.origin.y, 2)
		+ powf(ray.origin.z, 2);
	discriminant = powf(b, 2) - 4 * a * c;
	return ((t_distance){
		.a = a,
		.b = b,
		.c = c,
		.t1 = (-b - sqrtf(discriminant)) / (2 * a),
		.t2 = (-b + sqrtf(discriminant)) / (2 * a),
		.determinant = discriminant,
	});
}

/* static t_bool	check_cap(t_ray ray, float t, float cone_range)
{
	float	x;
	float	z;

	x = ray.origin.x + t * ray.direction.x;
	z = ray.origin.z + t * ray.direction.z;
	return ((powf(x, 2) + powf(z, 2)) <= powf(cone_range, 2));
}
 */
//if (check_cap(ray, t, shape->cone.minimum))
static void	intersect_caps(t_hit **xs, t_shape *shape, t_ray ray)
{
	float	t;
	float	x;
	float	z;

	if (!shape->cone.closed || fabsf(ray.direction.y) < EPSILON)
		return ;
	t = (shape->cone.minimum - ray.origin.y) / ray.direction.y;
	x = ray.origin.x + t * ray.direction.x;
	z = ray.origin.z + t * ray.direction.z;
	if ((powf(x, 2) + powf(z, 2)) <= fabsf(shape->cone.minimum) + EPSILON)
		insert_intersection(xs, intersection(t, shape));
	t = (shape->cone.maximum - ray.origin.y) / ray.direction.y;
	x = ray.origin.x + t * ray.direction.x;
	z = ray.origin.z + t * ray.direction.z;
	if ((powf(x, 2) + powf(z, 2)) <= fabsf(shape->cone.maximum) + EPSILON)
		insert_intersection(xs, intersection(t, shape));
}
