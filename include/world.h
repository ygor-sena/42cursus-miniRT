/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:17:44 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/25 18:33:47 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

// After project is done, check where is the better header to define EPSILON.
// Identifier is needed by prepare_computations()
# define EPSILON 0.00001

# include "lights.h"
# include "shapes.h"

typedef struct s_world
{
	int				object_count;
	t_shape			*objects;
	t_light			*lights;
	t_intersection	*xs;
}	t_world;

typedef struct s_comps
{
	float		t;
	t_object	object;
	t_point		point;
	t_sight		sight;
	t_bool		inside;
	t_tuple		over_point;
}	t_comps;

/* ************************************************************************** */
/*                                  WORLD.C                                   */
/* ************************************************************************** */

/**
 * @brief Finds all intersections between a ray and all objects in the world.
 *
 * @param world The world of objects to check for intersections.
 * @param ray The ray to check for intersections.
 *
 * @return (t_intersection) A pointer to the first intersection in the sorted
 * linked list of intersections or NULL if no intersections are found.
 */
t_intersection	*intersect_world(t_world *world, t_ray ray);

/**
 * @brief Precomputes information related to an intersection.
 *
 * Given an intersection between a ray and a shape, this function precomputes
 * the point where the intersection occurred in world space, the eye vector
 * pointing back towards the camera, and the normal vector at the point of
 * intersection. This precomputed information is stored in a new data structure
 * and returned.
 *
 * If the hit point occurs inside of a shape, the normal vector will be flipped
 * to point to the correct direction.
 *
 * @param intersection The intersection between the ray and a shape.
 * @param ray The ray that intersected with the shape.
 * @return (t_comps) A new data structure containing the precomputed information.
 */
t_comps			prepare_computations(t_intersection *intersection, t_ray ray);

/**
 * @brief Computes the color at an intersection in the given world.
 *
 * Given a world and a precomputed information about an intersection between a
 * ray and a shape, this function computes the color of the intersection point.
 * The color is computed by determining the light that hits the intersection and
 * blending that light with the color of the shape at that point. The resulting
 * color is returned.
 *
 * @param world The world in which the intersection occurred.
 * @param comps The precomputed information about the intersection.
 * @return (t_color) The color of the intersection point.
 */
t_color			shade_hit(t_world world, t_comps comps);

/**
 * @brief Computes the color at the intersection of a given ray with a world.
 *
 * Given a world and a ray, this function computes the color of the intersection
 * point between the ray and the shapes in the world. It first uses
 * intersect_world() to find the intersections between the ray and the shapes in
 * the world. If there are no intersections, the function returns the color
 * black. Otherwise, it selects the intersection that is closest to the ray's
 * origin and precomputes the necessary values for that intersection using
 * prepare_computations(). Finally, the function calls shade_hit() to compute
 * the color at the intersection and returns it.
 *
 * @param world The world in which the intersection occurred.
 * @param ray The ray that intersected with the shapes in the world.
 * @return (t_color) The color of the intersection point, or black if there is
 * no such intersection.
 */
t_color			color_at(t_world world, t_ray ray);

/* ************************************************************************** */
/*                                 SHADOWS.C                                  */
/* ************************************************************************** */

/**
 * @brief This function works the following way: a ray tracer computes shadows
 *        by casting a ray, called a shadow ray, from each point of intersection
 *        toward the light source. If something intersects that shadow ray
 *        between the point and the light source, then the point is considered
 *        to be in shadow. About the function calculations, magnitude(v) means
 *        the distance between the light's position and the given point. In
 *        turn, normalize(v) means its direction.
 * 
 * @param world Receives a world containing objects and light sources.
 * @param point Receives a point location of the world.
 * @return (t_bool) Returns TRUE is the point is in shadow. Otherwise, returns
 *         FALSE if the point isn't in shadow.
 */
t_bool			is_shadowed(t_world *world, t_tuple point);

#endif
