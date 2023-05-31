/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:05:41 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/31 11:27:49 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include "rays.h"
# include "materials.h"

# define EPSILON		0.00001

/**
 * @brief The structure t_sphere represents a sphere.
 *
 * @param origin Stores the sphere's origin point.
 * @param radius Stores the radius of the sphere.
 */
typedef struct s_sphere
{
	t_point	origin;
	float	radius;
}	t_sphere;

/**
 * @brief The structure t_plane represents a plane.
 *
 * @param origin Stores the plane's origin point.
 */
typedef struct s_plane
{
	t_point	origin;
}	t_plane;

/**
 * @brief The structure t_cylinder represents a cylinder.
 *
 * @param origin Stores the cylinder's origin point.
 * @param radius Stores the radius of the cylinder.
 * @param minimum Stores the cylinder's minimum height, i.e, lowest height.
 * @param maximum Stores the cylinder's maxinum height, i.e, highest height.
 * @param closed Stores TRUE, if the cylinder is capped or FALSE, if it isn't
 *               capped.
 */
typedef struct s_cylinder
{
	t_point	origin;
	float	radius;
	float	minimum;
	float	maximum;
	t_bool	closed;
}	t_cylinder;

/**
 * @brief The structure t_cone represents a cone.
 *
 * @param origin Stores the cone's origin point.
 * @param minimum Stores the cone's minimum height, i.e, lowest height.
 * @param maximum Stores the cone's maxinum height, i.e, highest height.
 * @param closed Stores TRUE, if the cone is capped or FALSE, if it isn't
 *               capped.
 */
typedef struct s_cone
{
	t_point	origin;
	float	minimum;
	float	maximum;
	t_bool	closed;
}	t_cone;

typedef struct s_shape		t_shape;
typedef struct s_hit		t_hit;
typedef t_bool				(*t_hit_record)(t_hit **, t_shape *, t_ray);
typedef t_tuple				(*t_normal_at)(t_shape *, t_tuple);

/**
 * @struct t_shape
 * @brief Represents a shape in a scene.
 *
 * @param shape This union of shapes represents the possible geometric forms the
 *        structure t_shape can assume, i.e., to be a sphere, a plane, a
 *        cylinder or a cone. Each shape has its own particular values. The
 *        fields below are common properties shared by all types of shape. Each
 *        one of them is going to be manipulated (transform, inverse and
 *        transpose), be made of some matter (material) and be intersected by
 *        rays (intersect and normal_at).
 * @param transform Stores the transformation matrix for the shape.
 * @param inverse Stores the inverse matrix for the shape.
 * @param transpose Stores the transpose matrix for the shape.
 * @param material Stores the material information of the shape.
 * @param intersect Stores the function's name used to calculate the
 *                  intersection of a ray with the shape.
 * @param normal_at Stores the function's name used to calculate the normal at a
 *                  point on the shape.
 */
typedef struct s_shape
{
	union {
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
		t_cone		cone;
	};
	t_matrix		transform;
	t_matrix		inverse;
	t_matrix		transpose;
	t_material		material;
	t_hit_record	intersect;
	t_normal_at		normal_at;
}	t_shape;

/**
 * @brief The structure t_hit stores a linked list of ray-shape intersections'
 *        values. 
 *
 * @param t Stores the distance between the origin of the ray and the point of
 *          intersection.
 * @param object Stores information about the shape that is being intersected.
 * @param next Stores the next intersection value of one ray casting, if any.
 */
typedef struct s_hit
{
	double	t;
	t_shape	*object;
	t_hit	*next;
}	t_hit;

/**
 * @brief This struct stores the necessary data to evaluate a ray-sphere
 *        intersection. To do that, it relies in geometry, trigonometry and the
 *        Pythagorean theorem. It's important to mention that discriminant means
 *        the number that says whether the ray intersects the sphere at all.
 *        For a detailed description, refer to: https://www.scratchapixel.com/
 *        lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/
 *        ray-sphere-intersection.html.
 *
 * @param a Stores a value from quadratic equation. This value is useful to
 *          identify if a ray is parallel or not to y axis of a given cylinder.
 * @param b Stores b value from quadratic equation derived from geometry rules.
 * @param c Stores c value from quadratic equation derived from geometry rules.
 * @param t1 Stores the distance from ray's origin up to the intersection of a
 *           given ray with shape's surface. If there is only one, it means the
 *           ray intersects the shape in only one point.
 * @param t2 Stores the distance from ray's origin up to the intersection of a
 *           given ray with shape's surface. The combination of positive and
 *           negative numbers of t1 and t2 will determine where the ray is
 *           intersecting the shape.
 * @param discriminant Stores the information about how the ray intersects a
 *                     given shape. If discriminant isless than 0, then the ray
 *                     doesn't intersect the shape. If discriminant is 0, the
 *                     ray intersects the shape in one place only. If the
 *                     discriminant is higher than 0, the ray intersects the
 *                     shape in two places.
 */
typedef struct s_discriminant
{
	double	a;
	double	b;
	double	c;
	double	t1;
	double	t2;
	double	discriminant;
}	t_discriminant;

/* ************************************************************************** */
/*                             INTERSECTIONS.C                                */
/* ************************************************************************** */

/**
 * @brief This function gets shape's intersection from ray's origin. If the ray
 *        is inside the shape, then there is one intersection in front of the
 *        ray and another one behind it. When the ray intersects the shape at
 *        one point only, the function returns two intersections with the same
 *        point each. This will be helpful when dealing with object overlaps in
 *        ch. 16 (Constructive Solid Geometry - CSG).
 *
 * @param xs A struct of type t_hit that stores intersections' values, if any.
 * @param sphere A struct of type t_shape containing a shape.
 * @param ray A struct of type t_ray containing a ray.
 * @return Returns `TRUE` if an intersection was found and added to the list.
 *         Otherwise, returns `FALSE`.
 */
t_bool			intersect(t_hit **xs, t_shape *shape, t_ray ray);

/**
 * @brief Creates a hit record for an intersection.
 *
 * This function creates a hit record for an intersection, which contains
 * information about the intersection such as the t value, the object that was
 * intersected, the color of the object, its material properties, and whether or
 * not it should be reflected. This information is used to draw the intersection
 * and to determine how it interacts with other objects in the scene.
 *
 * @param t A float value representing the distance between the origin of the ray
 *          and the point of intersection.
 * @param shape A pointer to a structure of type `t_shape` representing the
 *              object that was intersected.
 * @return Returns a pointer to a structure of type `t_hit` representing the hit
 *         record.
 */
t_hit			*intersection(float t, t_shape *shape);

/**
 * @brief Inserts a hit record into a list of intersections in order of
 *        increasing t value.
 *
 * This function inserts a hit record into a list of intersections in order of
 * increasing t value. The function takes a pointer to the list of intersections
 * represented by a pointer to a pointer to a structure of type `t_hit` and a
 * pointer to a structure of type `t_hit` representing the hit record to be
 * inserted. If the hit record has a smaller t value than any existing hit
 * records, it is inserted at the beginning of the list. Otherwise, the function
 * traverses the list of intersections and inserts the hit record at the
 * appropriate position.
 *
 * @param xs A pointer to a pointer to a structure of type `t_hit` representing
 *           the list of intersections.
 * @param isect A pointer to a structure of type `t_hit` representing the hit
 *              record to be inserted.
 */
void			insert_intersection(t_hit **xs, t_hit *i);

/**
 * @brief Determines the first hit from a list of intersections.
 *
 * By "hit", we mean the first intersection that is visible from the ray's
 * origin. It is possible to have intersections that are behind the ray or
 * that were hidden behind (or occluded by) other objects. The hit() function
 * takes a list of intersection records as a parameter and returns the first
 * visible intersection from the list.
 *
 * @param xs A pointer to a structure of type `t_hit` that stores a list of
 *           intersection records.
 * @return A pointer to a structure of type `t_hit` that represents the first
 *         visible intersection from the list of intersection records.
 */
t_hit			*hit(t_hit *xs);

/* ************************************************************************** */
/*                                 SHAPES.C                                   */
/* ************************************************************************** */

/**
 * @brief Creates a new shape with default properties.
 *
 * This function creates a new shape with default properties and returns a
 * structure of type `t_shape`. The returned shape can be further customized by
 * assigning specific properties to it using other functions.
 *
 * @return A structure of type `t_shape` representing a new shape with default
 *         properties.
 */
t_shape			new_shape(void);

/**
 * @brief Assigns a transformation matrix to a shape.
 *
 * The transformation matrix is applied to the shape by modifying its internal
 * transformation matrix. This matrix is used to transform the shape's vertices
 * and normals when rendering it.
 *
 * @param shape A pointer to a structure of type `t_shape` representing the shape
 *              to be transformed.
 * @param transform A matrix of type `t_matrix` containing the transformation
 *                  values to be set.
 */
void			set_transform(t_shape *shape, t_matrix transform);

/* ************************************************************************** */
/*                                SPHERES.C                                   */
/* ************************************************************************** */

/**
 * @brief Creates a new sphere with default properties.
 *
 * This function creates a new sphere with default properties by calling
 * `new_shape()` and then assigning specific properties to it. The function
 * returns a structure of type `t_shape` representing the new sphere.
 *
 * @return A structure of type `t_shape` representing a new sphere with default
 *         properties.
 */
t_shape			new_sphere(void);

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
t_tuple			normal_at_sphere(t_shape *shape, t_tuple world_point);

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
t_bool			intersect_sphere(t_hit **xs, t_shape *shape, t_ray ray);

/* ************************************************************************** */
/*                                PLANES.C                                    */
/* ************************************************************************** */

/**
 * @brief Creates a new plane with default properties.
 *
 * This function creates a new plane with default properties by calling
 * `new_shape()` and then assigning specific properties to it. The function
 * returns a structure of type `t_shape` representing the new plane.
 *
 * @return Returns a structure of type `t_shape` representing a new plane with
 *         default properties.
 */
t_shape			new_plane(void);

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
t_tuple			normal_at_plane(t_shape *shape, t_tuple world_point);

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
t_bool			intersect_plane(t_hit **xs, t_shape *shape, t_ray ray);

/* ************************************************************************** */
/*                               PATTERNS.C                                   */
/* ************************************************************************** */

/**
 * @brief This function applies a pattern texture on a given object at a given
 *        world location.
 * 
 * @param pattern Receives the pattern to be applied.
 * @param shape Represents the shape that will receive the pattern.
 * @param world_point Contains the world point at which the pattern's color
 *                    will be applied.
 * @return Returns the color for the given pattern, on the given shape, at the
 *         given world.
 */
t_color			pattern_at_shape(t_pattern pattern,
					t_shape *shape, t_tuple world_point);

/* ************************************************************************** */
/*                              MATERIALS.C                                   */
/* ************************************************************************** */

/**
 * @brief In a nutshell, the function adds together the material's ambient
 * diffuse, and specular componentes, weighted by the angles between the
 * different vectors. The material can receive dark or light exposure.
 * Dark exposure means that the material is exposed to light indirectly.
 * Thus, only ambient reflection is computed. Light exposure means that
 * the material is exposed to light directly and, in addition to ambient
 * reflection, the diffuse and specular reflection are also calculated.
 *
 * @param shape A struct of type t_shape that stores the shape's material
 *              color, ambient, diffuse, specular and shininess attributes.
 * @param light A struct of type t_light containing the light's source.
 * @param point A struct of type t_tuple of the point being illuminated.
 * @param sight A struct of type t_sight with the values of eye and normal
 *              vectors obtained from the Phong Reflection Model algorithm.
 * @return The function returns the final shading of that point.
 */
t_color			lighting(t_shape *shape, t_light light,
					t_tuple point, t_sight sight);

/* ************************************************************************** */
/*                               CYLINDERS.C                                  */
/* ************************************************************************** */

/**
 * @brief Creates a new cylinder with default properties.
 *
 * This function creates a new cylinder with default properties transform and
 * material by calling `new_shape()` and then assigning specific properties
 * origin, radius, maximum height, minimum height and closed (or capped) to it.
 * The function returns a structure of type `t_shape` representing the new
 * cylinder.
 *
 * @return Returns a structure of type `t_shape` representing a new cylinder
 *         with default properties.
 */
t_shape			new_cylinder(void);

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
t_bool			intersect_cylinder(t_hit **xs, t_shape *shape, t_ray ray);

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
t_tuple			normal_at_cylinder(t_shape *shape, t_tuple world_point);

/* ************************************************************************** */
/*                                 CONES.C                                    */
/* ************************************************************************** */

/**
 * @brief Creates a new cone with default properties.
 *
 * This function creates a new cone with default properties transform and
 * material by calling `new_shape()` and then assigning specific properties
 * origin, maximum height, minimum height and closed (or capped) to it.
 * The function returns a structure of type `t_shape` representing the new
 * cone.
 *
 * @return A structure of type `t_shape` representing a new cone with
 *         default properties.
 */
t_shape			new_cone(void);

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
t_bool			intersect_cone(t_hit **xs, t_shape *shape, t_ray ray);

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
t_tuple			normal_at_cone(t_shape *shape, t_tuple world_point);

/* ************************************************************************** */
/*                             DISCRIMINANTS.C                                */
/* ************************************************************************** */

/**
 * @brief This function returns the necessary data to evaluate a ray-sphere
 *        intersection. To do that, it relies in geometry, trigonometry and the
 *        Pythagorean theorem. It's important to mention that discriminant means
 *        the number that says whether the ray intersects the sphere at all.
 * 
 * @param sphere A pointer to a structure of type `t_sphere` representing the
 *               sphere to be (or not) intersected with a ray.
 * @param ray A structure of type `t_ray` representing the ray that is going to
 *            intersect (or not) the sphere.
 * @return Returns a structure of type `t_discriminant` with a, b, c values from
 *         quadratic equation derived from initial formulas as well as t1, t2
 *         and discriminant values. t1 and t2 are the distance from ray's origin
 *         up to the intersection of given ray with sphere's surface.
 */
t_discriminant	sphere_discriminant(t_sphere *sphere, t_ray ray);

/**
 * @brief This function returns the necessary data to evaluate a ray-cylinder
 *        intersection. To do that, it relies in geometry, trigonometry and the
 *        Pythagorean theorem. It's important to mention that discriminant means
 *        the number that says whether the ray intersects the cylinder at all.
 *
 * @param ray A structure of type `t_ray` representing the ray that is going to
 *            intersect (or not) the cylinder.
 * @return Returns a structure of type `t_discriminant` with a, b, c values from
 *         quadratic equation derived from initial formulas as well as t1, t2
 *         and discriminant values. t1 and t2 are the distance from ray's origin
 *         up to the intersection of given ray with cylinder's surface.
 */
t_discriminant	cylinder_discriminant(t_ray ray);

/**
 * @brief This function returns the necessary data to evaluate a ray-cone
 *        intersection. To do that, it relies in geometry, trigonometry and the
 *        Pythagorean theorem. It's important to mention that discriminant means
 *        the number that says whether the ray intersects the sphere at all.
 *
 * @param ray A structure of type `t_ray` representing the ray that is going to
 *            intersect (or not) the cone.
 * @return Returns a structure of type `t_discriminant` with a, b, c values from
 *         quadratic equation derived from initial formulas as well as t1, t2
 *         and discriminant values. t1 and t2 are the distance from ray's origin
 *         up to the intersection of given ray with cone's surface.
 */
t_discriminant	cone_discriminant(t_ray ray);

#endif
