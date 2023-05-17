/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:38:04 by yde-goes          #+#    #+#             */
/*   Updated: 2023/05/17 17:29:10 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"

static t_distance	calculate_distance(t_ray ray);
static void			intersect_caps(t_hit **xs, t_shape *shape, t_ray ray);
//static t_bool		check_cap(t_ray ray, float t);

t_shape	new_cylinder(void)
{
	t_shape	object;

	object = new_shape();
	object.cylinder.origin = point(0, 0, 0);
	object.cylinder.radius = 1.0;
	object.cylinder.minimum = -INFINITY;
	object.cylinder.maximum = INFINITY;
	object.cylinder.closed = FALSE;
	object.normal_at = normal_at_cylinder;
	object.intersect = intersect_cylinder;
	return (object);
}

// ray is parallel to the y axis
// ray does not intersect the cylinder
t_bool	intersect_cylinder(t_hit **xs, t_shape *shape, t_ray ray)
{
	t_distance	d;
	float		y0;
	float		y1;

	intersect_caps(xs, shape, ray);
	d = calculate_distance(ray);
	if (is_epsilon_zero(fabsf(d.a), 0.0) || d.determinant < 0)
		return (FALSE);
	if (d.t1 > d.t2)
		swap(&d.t1, &d.t2);
	y0 = ray.origin.y + d.t1 * ray.direction.y;
	y1 = ray.origin.y + d.t2 * ray.direction.y;
	if (shape->cylinder.minimum < y0 && y0 < shape->cylinder.maximum)
		insert_intersection(xs, intersection(d.t1, shape));
	if (shape->cylinder.minimum < y1 && y1 < shape->cylinder.maximum)
		insert_intersection(xs, intersection(d.t2, shape));
	return (TRUE);
}

static t_distance	calculate_distance(t_ray ray)
{
	float	a;
	float	b;
	float	c;
	float	discriminant;

	a = powf(ray.direction.x, 2) + powf(ray.direction.z, 2);
	b = (2 * ray.origin.x * ray.direction.x)
		+ (2 * ray.origin.z * ray.direction.z);
	c = powf(ray.origin.x, 2) + powf(ray.origin.z, 2) - 1;
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

t_tuple	normal_at_cylinder(t_shape *shape, t_tuple world_point)
{
	float	dist;

	dist = powf(world_point.x, 2) + powf(world_point.z, 2);
	if (dist < 1 && world_point.y >= shape->cylinder.maximum - EPSILON)
		return (vector(0, 1, 0));
	if (dist < 1 && world_point.y <= shape->cylinder.minimum + EPSILON)
		return (vector(0, -1, 0));
	return (vector(world_point.x, 0, world_point.z));
}

// caps only matter if the cylinder is closed, and might possibly be
// intersected by the ray.
// check for an intersection with the lower end cap by intersecting
// the ray with the plane at y=cyl.minimum
// check for an intersection with the upper end cap by intersecting
// the ray with the plane at y=cyl.maximum
static void	intersect_caps(t_hit **xs, t_shape *shape, t_ray ray)
{
	float	t;
	float	x;
	float	z;

	if (shape->cylinder.closed == FALSE || is_epsilon_zero(ray.direction.y, 0.0))
		return ;
	t = (shape->cylinder.minimum - ray.origin.y) / ray.direction.y;
	x = ray.origin.x + t * ray.direction.x;
	z = ray.origin.z + t * ray.direction.z;
	if ((powf(x, 2) + powf(z, 2)) <= 1 + EPSILON)
		insert_intersection(xs, intersection(t, shape));
	t = (shape->cylinder.maximum - ray.origin.y) / ray.direction.y;
	x = ray.origin.x + t * ray.direction.x;
	z = ray.origin.z + t * ray.direction.z;
	if ((powf(x, 2) + powf(z, 2)) <= 1 + EPSILON)
		insert_intersection(xs, intersection(t, shape));
}

// a helper function to reduce duplication.
// checks to see if the intersection at `t` is within
// a radius # of 1 (the radius of your cylinders) from
// the y axis.
/* static t_bool	check_cap(t_ray ray, float t)
{
	float	x;
	float	z;

	x = ray.origin.x + t * ray.direction.x;
	z = ray.origin.z + t * ray.direction.z;
	return ((powf(x, 2) + powf(z, 2)) <= 1 + EPSILON);
} */
