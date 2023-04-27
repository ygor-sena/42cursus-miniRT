/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_spheres.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 09:22:45 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/26 15:11:08 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "utils.h"

/* Test if a ray intersecting a sphere at two different points produces the
 * expected number of intersections and their respective values. */
Test(spheres, a_ray_intersect_a_sphere_at_two_points)
{
	t_ray			ray;
	t_shape			shape;
	t_intersection	*xs;

	xs = NULL;
	ray = new_ray(point(0, 0, -5), vector(0, 0, 1));
	shape = new_sphere();
	intersect(&xs, &shape, ray);
	cr_assert(eq(flt, xs->t, 4));
	cr_assert(eq(flt, xs->next->t, 6));
}

/* Test if a ray intersecting a sphere at a tangent produces the expected
 * number of intersections and their values. */
Test(spheres, a_ray_intersects_a_sphere_at_a_tangent)
{
	t_ray			ray;
	t_shape			shape;
	t_intersection	*xs;

	xs = NULL;
	ray = new_ray(point(0, 1, -5), vector(0, 0, 1));
	shape = new_sphere();
	intersect(&xs, &shape, ray);
	cr_assert(eq(flt, xs->t, 5));
	cr_assert(eq(flt, xs->next->t, 5));
}

/* Test if a ray missing a sphere completely results in no intersections. */
Test(spheres, a_ray_misses_a_sphere)
{
	t_ray			ray;
	t_shape			shape;
	t_intersection	*xs;

	xs = NULL;
	ray = new_ray(point(0, 2, -5), vector(0, 0, 1));
	shape = new_sphere();
	intersect(&xs, &shape, ray);
	cr_assert(eq(ptr, xs, NULL));
}

/* Tests whether a ray originating inside a sphere intersects the sphere at two
 * different points, with one point behind the ray and the other in front of it. */
Test(spheres, a_ray_originates_inside_a_sphere)
{
	t_ray			ray;
	t_shape			shape;
	t_intersection	*xs;

	xs = NULL;
	ray = new_ray(point(0, 0, 0), vector(0, 0, 1));
	shape = new_sphere();
	intersect(&xs, &shape, ray);

	cr_assert(eq(i32, intersection_count(xs), 2));
	cr_assert(eq(flt, xs->t, -1));
	cr_assert(eq(flt, xs->next->t, 1));
}

/* Tests that a sphere is behind a ray, and thus, the number of intersections
 * is two, with negative values */
Test(spheres, a_sphere_is_behind_a_ray)
{
	t_ray			ray;
	t_shape			shape;
	t_intersection	*xs;

	xs = NULL;
	ray = new_ray(point(0, 0, 5), vector(0, 0, 1));
	shape = new_sphere();
	intersect(&xs, &shape, ray);
	cr_assert(eq(i32, intersection_count(xs), 2));
	cr_assert(eq(flt, xs->t, -6));
	cr_assert(eq(flt, xs->next->t, -4));
}

/* Test if the intersect function correctly sets the object on the
 * intersection record for each intersection, by verifying that the
 * objects are correctly set to the sphere. */
Test(spheres, intersect_sets_the_object_on_the_intersection)
{
	t_ray			ray;
	t_shape			shape;
	t_intersection	*xs;

	xs = NULL;
	ray = new_ray(point(0, 0, -5), vector(0, 0, 1));
	shape = new_sphere();
	intersect(&xs, &shape, ray);
	cr_assert(eq(i32, intersection_count(xs), 2));
	cr_assert(eq(i32, compare_spheres(&xs->object[0].sphere, &shape.sphere), TRUE));
}

/* Tests the ability to intersect a ray with a scaled sphere */
Test(spheres, intersect_a_scaled_sphere_with_a_ray)
{
	t_ray			r;
	t_shape			s;
	t_intersection	*xs;

	xs = NULL;
	r = new_ray(point(0, 0, -5), vector(0, 0, 1));
	s = new_sphere();
	set_transform(&s, scaling(2, 2, 2));
	intersect(&xs, &s, r);
	cr_assert(eq(flt, xs->t, 3.0));
	cr_assert(eq(flt, xs->next->t, 7.0));
}

/* Tests the ability to intersect a ray with a translated sphere */
Test(spheres, intersect_a_translated_sphere_with_a_ray)
{
	t_ray			r;
	t_shape			s;
	t_intersection	*xs;

	xs = NULL;
	r = new_ray(point(0, 0, -5), vector(0, 0, 1));
	s = new_sphere();
	set_transform(&s, translation(5, 0, 0));
	intersect(&xs, &s, r);
	cr_assert(eq(ptr, xs, NULL));
}

/* Checks the normal on a sphere at a point on the x axis */
Test(spheres, normal_at_x_axis)
{
	t_shape		s;
	t_vector	n;
	t_tuple		res;

	s = new_sphere();
	n = normal_at(&s, point(1, 0, 0));
	res = vector(1, 0, 0);

	cr_assert(eq(flt, n.x, res.x));
	cr_assert(eq(flt, n.y, res.y));
	cr_assert(eq(flt, n.z, res.z));
	cr_assert(eq(flt, n.w, res.w));
}

/* Checks the normal on a sphere at a point on the y axis */
Test(spheres, normal_at_y_axis)
{
	t_shape		s;
	t_vector	n;
	t_tuple		res;

	s = new_sphere();
	n = normal_at(&s, point(0, 1, 0));
	res = vector(0, 1, 0);

	cr_assert(eq(flt, n.x, res.x));
	cr_assert(eq(flt, n.y, res.y));
	cr_assert(eq(flt, n.z, res.z));
	cr_assert(eq(flt, n.w, res.w));
}

/* Checks the normal on a sphere at a point on the z axis */
Test(spheres, normal_at_z_axis)
{
	t_shape		s;
	t_vector	n;
	t_tuple		res;

	s = new_sphere();
	n = normal_at(&s, point(0, 0, 1));
	res = vector(0, 0, 1);

	cr_assert(eq(flt, n.x, res.x));
	cr_assert(eq(flt, n.y, res.y));
	cr_assert(eq(flt, n.z, res.z));
	cr_assert(eq(flt, n.w, res.w));
}

/* Checks the normal on a sphere at a nonaxial point */
Test(spheres, normal_at_nonaxial_pt)
{
	t_shape		s;
	t_vector	n;
	t_tuple		res;
	float		coord;

	s = new_sphere();
	coord = sqrtf(3.0)/3.0;
	n = normal_at(&s, point(coord, coord, coord));
	res = vector(coord, coord, coord);

	cr_assert_float_eq(n.x, res.x, EPSILON);
	cr_assert_float_eq(n.y, res.y, EPSILON);
	cr_assert_float_eq(n.z, res.z, EPSILON);
	cr_assert_float_eq(n.w, res.w, EPSILON);
}

/**
 * Checks the feature of a normal vector which states
 * that surface/normal vector should always be normalized.
 * Refer to the book TRTC on p.78
 */
Test(spheres, normal_is_normalized_vector)
{
	t_shape		s;
	t_vector	n;
	t_tuple		res;
	float		coord;

	s = new_sphere();
	coord = sqrtf(3.0)/3.0;
	n = normal_at(&s, point(coord, coord, coord));
	res = normalize(n);

	cr_assert_float_eq(n.x, res.x, EPSILON);
	cr_assert_float_eq(n.y, res.y, EPSILON);
	cr_assert_float_eq(n.z, res.z, EPSILON);
	cr_assert_float_eq(n.w, res.w, EPSILON);
}

/**
 * Checks the normal/surface vector when the sphere's
 * origin is not longer at the world origin.
 */
Test(spheres, normal_on_a_translated_sphere)
{
	t_shape		s;
	t_vector	n;
	t_tuple		res;

	s = new_sphere();
	set_transform(&s, translation(0.0, 1.0, 0.0));
	n = normal_at(&s, point(0, 1.70711, -0.70711));
	res = vector(0, 0.70711, -0.70711);

	cr_assert_float_eq(n.x, res.x, EPSILON);
	cr_assert_float_eq(n.y, res.y, EPSILON);
	cr_assert_float_eq(n.z, res.z, EPSILON);
	cr_assert_float_eq(n.w, res.w, EPSILON);
}

/**
 * Checks the normal/surface vector when the sphere's
 * origin is not longer at the world origin.
 */
Test(spheres, normal_on_a_transformed_sphere)
{
	t_shape		s;
	t_vector	n;
	t_matrix	m;
	t_tuple		res;
	float		coord;

	s = new_sphere();
	m = multiply_mx_mx(scaling(1, 0.5, 1),
			rotation_z((float) M_PI/5.0));
	set_transform(&s, m);
	coord = sqrtf(2)/2.0;
	n = normal_at(&s, point(0, coord, -coord));
	res = vector(0, 0.97014, -0.24254);
	cr_assert_float_eq(n.x, res.x, EPSILON);
	cr_assert_float_eq(n.y, res.y, EPSILON);
	cr_assert_float_eq(n.z, res.z, EPSILON);
	cr_assert_float_eq(n.w, res.w, EPSILON);
}

/* Checks if the default values of a sphere instance */
Test(spheres, sphere_default_material)
{
	t_shape		s;
	t_material	m;

	s = new_sphere();
	m = material();
	m.ambient = 1;
	s.material = m;

	cr_assert(eq(flt, s.material.ambient, m.ambient));
	cr_assert(eq(flt, s.material.diffuse, m.diffuse));
	cr_assert(eq(flt, s.material.specular, m.specular));
	cr_assert(eq(flt, s.material.shininess, m.shininess));
}
