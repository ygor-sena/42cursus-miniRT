/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:17:44 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/30 18:19:41 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "lights.h"
# include "shapes.h"

/**
 * @brief This struct contains everything related to the building of a ray
 *        tracing's world. The world has objects (or shapes), point lights and
 *        an ambient color.
 *
 * @param xs A struct of type t_hit that stores intersections' values, if any.
 * @param object_count Stores the information about how many shapes there are in
 *                     the world.
 * @param objects A list of objects (or shapes) that exist in the world. They
 *                can be a cone, a sphere, a plane or a cylinder.
 * @param light_count Stores the information about how many point lights there
 *                    are in the world.
 * @param lights A list of point lights that exist in the world.
 * @param ambient Represents the ambient color in the world.
 */
typedef struct s_world
{
	t_hit	*xs;
	int		object_count;
	t_shape	*objects;
	int		light_count;
	t_light	*lights;
	t_color	ambient;
}	t_world;

/**
 * @brief This structure of type t_comps stores some precomputed values that are
 *        useful when working intersections and their color calculations.
 *
 * @param t Stores the intersection value at a given point, if any.
 * @param object Stores shape's data.
 * @param point Stores a point to be used as referenece.
 * @param sight Stores the human's eye data used as reference.
 * @param inside Stores TRUE or FALSE in regards to whether a hit occurs inside
 *               the object (or shape). If hit is inside the shape, the value is
 *               TRUE. Otherwise, it's is FALSE. It works together with the field
 *               over_point to fix a problem called acne.
 * @param over_point This field avoids the effect called acne, which happens
 *                   because computers cannot represent floating points very
 *                   well. Because of that, sometimes the calculation of the
 *                   ray-surface intersection will result in a point of
 *                   intersection that lies beneath the actual surface of a
 *                   given shape. This field sets a margin of error.
 */
typedef struct s_comps
{
	float	t;
	t_shape	*object;
	t_point	point;
	t_sight	sight;
	t_bool	inside;
	t_tuple	over_point;
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
 * @return Returns a  pointer to the first intersection in the sorted linked
 *         list of intersections or NULL if no intersections are found.
 */
t_hit	*intersect_world(t_world *world, t_ray ray);

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
 * @return Returns a new data structure containing the precomputed information.
 */
t_comps	prepare_computations(t_hit *intersection, t_ray ray);

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
 * @return Returns the color of the intersection point.
 */
t_color	shade_hit(t_world world, t_comps comps);

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
 * @return Returns the color of the intersection point, or black if there is no
 *         such intersection.
 */
t_color	color_at(t_world world, t_ray ray);

/* ************************************************************************** */
/*                                 SHADOWS.C                                  */
/* ************************************************************************** */

/**
 * @brief Determines whether a point in a world is in shadow or not.
 *
 * This function works by casting a shadow ray from the given point towards each
 * light source in the world. If the shadow ray intersects any objects in the
 * world before reaching the light source, the point is considered to be in
 * shadow. The function calculates the distance between the light source and
 * the given point using the magnitude of the vector between them, and normalizes
 * the vector to get its direction.
 *
 * @param world A pointer to a structure of type `t_world` representing the
 *              world containing objects and light sources.
 * @param point A structure of type `t_tuple` representing the location of the
 *              point in the world.
 * @param index An index representing which point light is being passed to the
 *              function. It's possible to have more than one.
 * @return Returns `TRUE` if the point is in shadow. Otherwise, returns `FALSE`
 *         if the point is not in shadow.
 */
t_bool	is_shadowed(t_world *world, t_tuple point, int index);

#endif
