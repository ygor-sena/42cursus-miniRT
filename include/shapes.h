/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:05:41 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/17 20:10:41 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include "rays.h"
# include "materials.h"

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

typedef struct s_intersection
{
	float					t;
	t_object				object;
	struct s_intersection	*next;
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

t_intersection	*intersect(t_sphere *sphere, t_ray ray);
void			set_transform(t_sphere *sphere, t_matrix transform);

/**
 * @brief A surface normal or normal vector is a vector that points
 *	perpendicular to a surface at a given point. This function calculates the
 *	perpendicular vector of a point on a sphere. To do this, the function
 *	draws a vector from the origin point of the sphere to the world point
 *	passed as the second parameter, i.e., the point on the sphere's surface.
 *
 * @param sphere A struct of type t_sphere containing an initialized sphere.
 * @param world_point A struct of type t_tuple refering to the world point on
 *	the given sphere's surface.
 * @return (t_tuple) A normal vector perpendicular to the given world point on
 *	a given sphere's surface.
 */
t_tuple			normal_at(t_sphere sphere, t_tuple world_point);

/* ************************************************************************** */
/*                             INTERSECTIONS.C                                */
/* ************************************************************************** */

t_intersection	*intersection(float t, t_sphere *sphere);
void			insert_intersection(t_intersection **xs, t_intersection *i);
t_intersection	*hit(t_intersection *xs);
int				intersection_count(t_intersection *xs);
void			erase_intersections(t_intersection **xs);

#endif
