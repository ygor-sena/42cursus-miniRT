/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spheres.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:30:21 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/06/08 19:03:38 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "patterns.h"
#include "shapes.h"

static t_bool	intersect_sphere(t_hit **xs, t_shape *shape, t_ray ray);
static t_vector	normal_at_sphere(t_shape *shape, t_point object_point);

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
	object.checker = uv_checkers(16, 8, new_color(0, 0, 0), new_color(1, 1, 1));
	object.map = spherical_map;
	return (object);
}

/**
 * @brief Calculates the intersection points between a ray and a sphere.
 *
 * This function calculates the intersection points between a ray and a sphere.
 * If the ray starts inside the sphere, there are two intersection points: one
 * in front of the ray and one behind it. When the ray intersects the sphere at
 * one point only, the function returns two identical intersection points. This
 * is useful when dealing with object overlaps in Constructive Solid Geometry
 * (CSG).
 *
 * @param xs A pointer to a pointer of type `t_hit` representing the collection
 *           of intersection points.
 * @param shape A pointer to a structure of type `t_shape` representing the
 *              sphere to be intersected.
 * @param ray A structure of type `t_ray` representing the ray to be intersected
 *            with the sphere.
 * @return Returns `TRUE` if an intersection was found, `FALSE` otherwise.
 */
static t_bool	intersect_sphere(t_hit **xs, t_shape *shape, t_ray ray)
{
	t_discriminant	d;

	d = sphere_discriminant(&shape->sphere, ray);
	if (d.discriminant < 0)
		return (FALSE);
	insert_intersection(xs, intersection(d.t1, shape));
	insert_intersection(xs, intersection(d.t2, shape));
	return (TRUE);
}

/**
 * @brief Calculates the normal vector at a given point on a sphere's surface.
 *
 * A surface normal, or normal vector, is a vector that points perpendicular
 * to a surface at a given point. This function calculates the normal vector
 * at a specified point on the surface of a sphere. The normal vector is
 * essential in various applications, such as shading and collision detection.
 *
 * The function computes the normal vector by drawing a vector from the
 * sphere's origin to the world point passed as the second parameter. This
 * world point refers to the point on the sphere's surface for which the
 * normal vector is to be calculated.
 *
 * @param sphere A struct of type t_sphere containing an initialized sphere.
 * @param world_point A struct of type t_tuple referring to the world point on
 *                    the given sphere's surface.
 * @return A normal vector perpendicular to the given world point on
 *         a given sphere's surface.
 */
static t_vector	normal_at_sphere(t_shape *shape, t_point object_point)
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
