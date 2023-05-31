/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:43:18 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/26 01:27:03 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"

static t_vector	normal_at_plane(t_shape *shape, t_point world_point);
static t_bool	intersect_plane(t_hit **xs, t_shape *shape, t_ray ray);

t_shape	new_plane(void)
{
	t_shape	object;

	object = new_shape();
	object.normal_at = normal_at_plane;
	object.intersect = intersect_plane;
	object.plane.origin = point(0, 0, 0);
	object.material.specular = 0.5;
	return (object);
}

/**
 * @brief Calculates the normal vector at a point on a plane.
 *
 * This function calculates the normal vector at a given point on a plane. The
 * normal vector is a vector that is perpendicular to the plane at the given
 * point.
 *
 * @param shape A pointer to a structure of type `t_shape` representing the
 *              plane.
 * @param world_point A tuple representing the point on the plane in world
 *                    coordinates.
 * @return Returns a tuple representing the normal vector at the given point.
 */
static t_vector	normal_at_plane(t_shape *shape, t_point world_point)
{
	(void) shape;
	(void) world_point;
	return (vector(0, 1, 0));
}

/**
 * @brief Calculates the intersection of a ray with a plane.
 *
 * This function calculates the intersection of a ray with a plane that extends
 * infinitely in the xz plane and passes through the origin. The function
 * returns a boolean value indicating whether the ray intersects the plane.
 * If the ray intersects the plane, the function adds a hit record to the list
 * of intersections.
 *
 * @param xs A pointer to a pointer to a structure of type `t_hit` representing
 *           the list of intersections.
 * @param shape A pointer to a structure of type `t_shape` representing the
 *              plane.
 * @param ray A structure of type `t_ray` representing the ray.
 * @return Returns a boolean value indicating whether the ray intersects the
 *         plane.
 */
static t_bool	intersect_plane(t_hit **xs, t_shape *shape, t_ray ray)
{
	float	t;

	if (fabs(ray.direction.y) < EPSILON)
		return (FALSE);
	t = -ray.origin.y / ray.direction.y;
	insert_intersection(xs, intersection(t, shape));
	return (TRUE);
}
