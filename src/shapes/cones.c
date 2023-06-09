/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cones.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:56:52 by yde-goes          #+#    #+#             */
/*   Updated: 2023/06/08 21:28:54 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"

static void		intersect_caps(t_hit **xs, t_shape *shape, t_ray ray);
static t_bool	check_cap(t_ray ray, double t, double cone_range);
static t_tuple	normal_at_cone(t_shape *shape, t_tuple world_point);
static t_bool	intersect_cone(t_hit **xs, t_shape *shape, t_ray ray);

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
	object.checker = uv_checkers(2, 2, new_color(0, 0, 0), new_color(1, 1, 1));
	object.map = cylindrical_map;
	return (object);
}

/**
 * @brief Calculates the normal vector at a point on a cone.
 *
 * This function calculates the normal vector at a given point on a cone.
 * The normal vector is a vector that is perpendicular to the cone at the
 * given point.
 *
 * @param shape A pointer to a structure of type `t_shape` representing the
 *              cone.
 * @param world_point A tuple representing the point on the cone in world
 *                    coordinates.
 * @return Returns a tuple representing the normal vector at the given point.
 */
static t_tuple	normal_at_cone(t_shape *shape, t_tuple world_point)
{
	double	dist;
	double	min_radius;
	double	max_radius;
	double	y;

	dist = pow(world_point.x, 2) + pow(world_point.z, 2);
	max_radius = pow(shape->cone.maximum, 2);
	if (dist < max_radius && world_point.y >= shape->cone.maximum - EPSILON)
		return (vector(0, 1, 0));
	min_radius = pow(shape->cone.minimum, 2);
	if (dist < min_radius && world_point.y <= shape->cone.minimum + EPSILON)
		return (vector(0, -1, 0));
	y = sqrt(dist);
	if (world_point.y > 0.0)
		y = -y;
	return (vector(world_point.x, y, world_point.z));
}

/*
 * Codeflow: check for caps and then calculate the discriminant. If a is nearly
 * zero, then the ray is parallel to the y axis and there's one intersection
 * point which uses a specific formula. If both a and b is zero, the ray misses
 * the halves of the cone. If discriminant is zero, then the ray does not
 * intersect the cone.
 */

/**
 * @brief This function calculates the intersection of a ray with a cone.
 *
 * It first checks if there are any intersections on the sides of the cone.
 * Then, it proceeds to check for intersections within the end caps. If any
 * intersection is found, the function computes the intersection of the sides and
 * end caps, respectively.
 *
 * @param xs A pointer to a pointer to a structure of type `t_hit` representing
 *           the list of intersections.
 * @param shape A pointer to a structure of type `t_shape` representing the
 *              cone.
 * @param ray A structure of type `t_ray` representing the ray.
 * @return Returns a boolean value indicating whether the ray intersects the
 *         cone.
 */
static t_bool	intersect_cone(t_hit **xs, t_shape *shape, t_ray ray)
{
	t_discriminant	d;
	double			y0;
	double			y1;

	intersect_caps(xs, shape, ray);
	d = cone_discriminant(ray);
	if (fabs(d.a) < EPSILON)
	{
		if (fabs(d.b) < EPSILON)
			return (FALSE);
		insert_intersection(xs, intersection((-d.c) / (2.0 * d.b), shape));
		return (TRUE);
	}
	if (d.discriminant < 0.0)
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

static void	intersect_caps(t_hit **xs, t_shape *shape, t_ray ray)
{
	double	t;

	if (!shape->cone.closed || fabs(ray.direction.y) < EPSILON)
		return ;
	t = (shape->cone.minimum - ray.origin.y) / ray.direction.y;
	if (check_cap(ray, t, shape->cone.minimum))
		insert_intersection(xs, intersection(t, shape));
	t = (shape->cone.maximum - ray.origin.y) / ray.direction.y;
	if (check_cap(ray, t, shape->cone.maximum))
		insert_intersection(xs, intersection(t, shape));
}

static t_bool	check_cap(t_ray ray, double t, double cone_range)
{
	double	x;
	double	z;

	x = ray.origin.x + t * ray.direction.x;
	z = ray.origin.z + t * ray.direction.z;
	return ((pow(x, 2) + pow(z, 2)) <= pow(cone_range, 2));
}
