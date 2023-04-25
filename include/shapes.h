/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:05:41 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/25 11:44:54 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include "rays.h"
# include "materials.h"

typedef enum e_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	SHAPE_COUNT
}	t_type;

typedef struct s_sphere
{
	t_point		origin;
	float		radius;
	t_matrix	transform;
	t_material	material;
}	t_sphere;

typedef union u_object
{
	t_sphere	*sphere;
}	t_object;

typedef struct s_shape
{
	union {
		t_sphere	sphere;
	};
	t_matrix	transform;
	t_material	material;
	t_type		id;
}	t_shape;

typedef struct s_intersection	t_intersection;
typedef struct s_intersection
{
	float			t;
	t_object		object;
	t_intersection	*next;
}	t_intersection;

typedef struct s_distance
{
	float	t1;
	float	t2;
	float	determinant;
}	t_distance;

/* ************************************************************************** */
/*                                SPHERES.C                                   */
/* ************************************************************************** */

/**
 * @brief This function gets sphere's intersection from ray's origin. If the ray
 *        is inside the sphere, there is one intersection in front of the ray
 *        and another one behind it. When the ray intersects the sphere at one
 *        point only, the function returns two intersections with the same point
 *        each. This will be helpful when dealing with object overlaps in ch. 16
 *        (Constructive Solid Geometry - CSG).
 *
 * @param sphere A struct of type t_sphere containing a sphere.
 * @param ray A struct of type t_ray containing a ray.
 * @return (t_intersection *) Returns the collection of t values where the ray
 *         intersects the sphere.
 */
// t_intersection	*intersect(t_sphere *sphere, t_ray ray);

/**
 * @brief The function set_transform() allows a transformation obtained from the
 *        function transform() to be assigned to a sphere.
 * 
 * @param sphere A struct of type t_sphere storing the sphere to be transformed.
 * @param transform A matrix containing the transformation's values to be set.
 */
void			set_transform(t_sphere *sphere, t_matrix transform);

/**
 * @brief A surface normal or normal vector is a vector that points
 * perpendicular to a surface at a given point. This function calculates the
 * perpendicular vector of a point on a sphere. To do this, the function
 * draws a vector from the origin point of the sphere to the world point
 * passed as the second parameter, i.e., the point on the sphere's surface.
 *
 * @param sphere A struct of type t_sphere containing an initialized sphere.
 * @param world_point A struct of type t_tuple refering to the world point on
 * the given sphere's surface.
 * @return (t_tuple) A normal vector perpendicular to the given world point on
 * a given sphere's surface.
 */
t_tuple			normal_at(t_sphere sphere, t_tuple world_point);

/* ************************************************************************** */
/*                             INTERSECTIONS.C                                */
/* ************************************************************************** */

/**
 * @brief One a set of t values has been defined with intersect(). This function
 *        more parameters to know how to draw the handful intersections that
 *        were found. i.e., what object was intersected at a given point, what
 *        color is it, what are its material properties, if should there be a
 *        reflection or not and so on.  
 *
 * @param t Receives the t value of the intersection.
 * @param sphere Receives the object that was intersected.
 * @return (t_intersection *) Returns a structure which aggregates the two
 *         arguments passed as parameter.
 */
t_intersection	*intersection(float t, t_sphere *sphere);

void			insert_intersection(t_intersection **xs, t_intersection *i);

/**
 * @brief By hit, we mean the visible intersections from ray's origin. After
 *        all, it's possible to have intersections that are behind the ray or
 *        that were hidden behind (or occluded by) other objects. To sum up, the
 *        function hit() gets the visible intersections the argument passed as
 *        parameter to the function.
 * 
 * @param xs A struct of type t_intersection storing a collection of
 *           intersection records.
 * @return (t_intersection *) Returns the hit from a collection of intersection
 *         records.
 */
t_intersection	*hit(t_intersection *xs);

int				intersection_count(t_intersection *xs);
void			erase_intersections(t_intersection **xs);

t_sphere		*new_sphere(void);

// TESTING:
t_shape			new_shape(void);
t_shape			sphere(void);
t_bool			intersect(t_intersection **xs, t_sphere *sphere, t_ray r);

#endif
