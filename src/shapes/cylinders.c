/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:38:04 by yde-goes          #+#    #+#             */
/*   Updated: 2023/06/08 21:30:43 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"

static void		intersect_caps(t_hit **xs, t_shape *shape, t_ray ray);
static t_bool	check_cap(t_ray ray, double t);
static t_bool	intersect_cylinder(t_hit **xs, t_shape *shape, t_ray ray);
static t_tuple	normal_at_cylinder(t_shape *shape, t_tuple world_point);

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
	object.checker = uv_checkers(2, 2, new_color(0, 0, 0), new_color(1, 1, 1));
	object.map = cylindrical_map;
	return (object);
}

/**
 * @brief This function calculates the intersection of a ray with a cylinder.
 *
 * It first checks if there are any intersections on the sides of the cylinder.
 * Then, it proceeds to check for intersections within the end caps. If any
 * intersection is found, the function computes the intersection of the sides and
 * end caps, respectively.
 *
 * @param xs A pointer to a pointer to a structure of type `t_hit` representing
 *           the list of intersections.
 * @param shape A pointer to a structure of type `t_shape` representing the
 *              cylinder.
 * @param ray A structure of type `t_ray` representing the ray.
 * @return Returns a boolean value indicating whether the ray intersects the
 *         cylinder.
 */
t_bool	intersect_cylinder(t_hit **xs, t_shape *shape, t_ray ray)
{
	t_discriminant	d;
	double			y0;
	double			y1;

	intersect_caps(xs, shape, ray);
	d = cylinder_discriminant(ray);
	if (fabs(d.a) < EPSILON || d.discriminant < 0.0)
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

/**
 * @brief Calculates the normal vector at a point on a cylinder.
 *
 * This function calculates the normal vector at a given point on a cylinder.
 * The normal vector is a vector that is perpendicular to the cylinder at the
 * given point.
 *
 * @param shape A pointer to a structure of type `t_shape` representing the
 *              cylinder.
 * @param world_point A tuple representing the point on the cylinder in world
 *                    coordinates.
 * @return Returns a tuple representing the normal vector at the given point.
 */
t_tuple	normal_at_cylinder(t_shape *shape, t_tuple world_point)
{
	double	dist;

	dist = pow(world_point.x, 2) + pow(world_point.z, 2);
	if (dist < 1.0 && world_point.y >= shape->cylinder.maximum - EPSILON)
		return (vector(0, 1, 0));
	if (dist < 1.0 && world_point.y <= shape->cylinder.minimum + EPSILON)
		return (vector(0, -1, 0));
	return (vector(world_point.x, 0.0, world_point.z));
}

// caps only matter if the cylinder is closed, and might possibly be
// intersected by the ray.
// check for an intersection with the lower end cap by intersecting
// the ray with the plane at y=cyl.minimum
// check for an intersection with the upper end cap by intersecting
// the ray with the plane at y=cyl.maximum
static void	intersect_caps(t_hit **xs, t_shape *shape, t_ray ray)
{
	double	t;

	if (shape->cylinder.closed == FALSE
		|| fabs(ray.direction.y) < EPSILON)
		return ;
	t = (shape->cylinder.minimum - ray.origin.y) / ray.direction.y;
	if (check_cap(ray, t))
		insert_intersection(xs, intersection(t, shape));
	t = (shape->cylinder.maximum - ray.origin.y) / ray.direction.y;
	if (check_cap(ray, t))
		insert_intersection(xs, intersection(t, shape));
}

// a helper function to reduce duplication.
// checks to see if the intersection at `t` is within
// a radius # of 1 (the radius of your cylinders) from
// the y axis.
static t_bool	check_cap(t_ray ray, double t)
{
	double	x;
	double	z;

	x = ray.origin.x + t * ray.direction.x;
	z = ray.origin.z + t * ray.direction.z;
	return ((pow(x, 2) + pow(z, 2)) <= 1.0);
}
