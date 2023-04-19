/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:17:44 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/19 11:39:11 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "lights.h"
# include "shapes.h"

// PERF: use arrays
typedef struct s_world
{
	t_list	*objects;
	t_list	*lights;
}	t_world;

typedef struct s_comps
{
	float		t;
	t_object	object;
	t_point		point;
	t_sight		sight;
	t_bool		inside;
}	t_comps;

/**
 * @brief Find all intersections between a ray and all objects in the world.
 *
 * @param world The world of objects to check for intersections.
 * @param ray The ray to check for intersections.
 *
 * @return A pointer to the first intersection in the sorted linked list of
 * intersections, or NULL if no intersections are found.
 */
t_intersection	*intersect_world(t_world *world, t_ray ray);

/**
 * @brief Precomputes information relating to an intersection.
 *
 * Given an intersection between a ray and a shape, this function precomputes
 * the point where the intersection occurred in world space, the eye vector
 * pointing back toward the camera, and the normal vector at the point of
 * intersection. This precomputed information is stored in a new data structure
 * and returned.
 *
 * If the hit occurs on the inside of a shape, the normal vector will be flipped
 * to point in the correct direction.
 *
 * @param intersection The intersection between the ray and a shape.
 * @param ray The ray that intersected with the shape.
 * @return A new data structure containing the precomputed information.
 */
t_comps			prepare_computations(t_intersection *intersection, t_ray ray);

/**
 * @brief Computes the color at an intersection in the given world.
 *
 * Given a world and precomputed information about an intersection between a
 * ray and a shape, this function computes the color of the intersection point.
 * The color is computed by determining the light that hits the intersection and
 * blending that light with the color of the shape at that point. The resulting
 * color is returned.
 *
 * @param world The world in which the intersection occurred.
 * @param comps The precomputed information about the intersection.
 * @return The color of the intersection point.
 */
t_color			shade_hit(t_world world, t_comps comps);

/**
 * @brief Computes the color at the intersection of a given ray with a world.
 *
 * Given a world and a ray, this function computes the color of the intersection
 * point between the ray and the shapes in the world. It first uses
 * intersect_world to find the intersections between the ray and the shapes in
 * the world. If there are no intersections, the function returns the color
 * black. Otherwise, it selects the intersection that is closest to the ray's
 * origin and precomputes the necessary values for that intersection using
 * prepare_computations. Finally, the function calls shade_hit to compute the
 * color at the intersection and returns it.
 *
 * @param world The world in which the intersection occurred.
 * @param ray The ray that intersected with the shapes in the world.
 * @return The color of the intersection point, or black if there is no such
 * intersection.
 */
t_color			color_at(t_world world, t_ray ray);

#endif
