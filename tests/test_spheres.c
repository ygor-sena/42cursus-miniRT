/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_spheres.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 09:22:45 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/14 14:37:43 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "utils.h"

Test(spheres, a_ray_intersect_a_sphere_at_two_points)
{
	t_ray			ray;
	t_sphere		*sphere;
	t_intersection	*xs;

	ray = new_ray(point(0, 0, -5), vector(0, 0, 1));
	sphere = sphere_stub();
	xs = intersect(sphere, ray);
	cr_assert(eq(flt, xs->t, 4));
	cr_assert(eq(flt, xs->next->t, 6));
	erase_intersections(&xs);
	free(sphere);
}

Test(spheres, a_ray_intersects_a_sphere_at_a_tangent)
{
	t_ray			ray;
	t_sphere		*sphere;
	t_intersection	*xs;

	ray = new_ray(point(0, 1, -5), vector(0, 0, 1));
	sphere = sphere_stub();
	xs = intersect(sphere, ray);
	cr_assert(eq(flt, xs->t, 5));
	cr_assert(eq(flt, xs->next->t, 5));
	erase_intersections(&xs);
	free(sphere);
}

Test(spheres, a_ray_misses_a_sphere)
{
	t_ray			ray;
	t_sphere		*sphere;
	t_intersection	*xs;

	ray = new_ray(point(0, 2, -5), vector(0, 0, 1));
	sphere = sphere_stub();
	xs = intersect(sphere, ray);
	cr_assert(eq(ptr, xs, NULL));
	erase_intersections(&xs);
	free(sphere);
}

Test(spheres, a_ray_originates_inside_a_sphere)
{
	t_ray			ray;
	t_sphere		*sphere;
	t_intersection	*xs;

	ray = new_ray(point(0, 0, 0), vector(0, 0, 1));
	sphere = sphere_stub();
	xs = intersect(sphere, ray);

	cr_assert(eq(i32, intersection_count(xs), 2));
	cr_assert(eq(flt, xs->t, -1));
	cr_assert(eq(flt, xs->next->t, 1));
	erase_intersections(&xs);
	free(sphere);
}

Test(spheres, a_sphere_is_behind_a_ray)
{
	t_ray			ray;
	t_sphere		*sphere;
	t_intersection	*xs;

	ray = new_ray(point(0, 0, 5), vector(0, 0, 1));
	sphere = sphere_stub();
	xs = intersect(sphere, ray);
	cr_assert(eq(i32, intersection_count(xs), 2));
	cr_assert(eq(flt, xs->t, -6));
	cr_assert(eq(flt, xs->next->t, -4));
	erase_intersections(&xs);
	free(sphere);
}

Test(spheres, intersect_sets_the_object_on_the_intersection)
{
	t_ray			ray;
	t_sphere		*sphere;
	t_intersection	*xs;

	xs = NULL;
	ray = new_ray(point(0, 0, -5), vector(0, 0, 1));
	sphere = sphere_stub();
	xs = intersect(sphere, ray);
	cr_assert(eq(i32, intersection_count(xs), 2));
	cr_assert(eq(i32, compare_spheres(xs->object.sphere, sphere), TRUE));
	cr_assert(eq(i32, compare_spheres(xs->object.sphere, sphere), TRUE));
	erase_intersections(&xs);
	free(sphere);
}

Test(spheres, a_spheres_default_transformation)
{
	t_sphere	*sphere;

	sphere = sphere_stub();
	cr_assert(eq(
		i32,
		compare_matrix(sphere->transform, get_identity_matrix()), 0)
	);
	free(sphere);
}

Test(spheres, changing_a_spheres_transformation)
{
	t_sphere	s;
	t_matrix	t;

	t = translation(2, 3, 4);
	set_transform(&s, t);
	cr_assert(eq(
		i32,
		compare_matrix(s.transform, t), 0)
	);
}

Test(spheres, intersect_a_scaled_sphere_with_a_ray)
{
	t_ray			r;
	t_sphere		*s;
	t_intersection	*xs;

	r = new_ray(point(0, 0, -5), vector(0, 0, 1));
	s = sphere_stub();
	set_transform(s, scaling(2, 2, 2));
	xs = intersect(s, r);
	cr_assert(eq(flt, xs->t, 3.0));
	cr_assert(eq(flt, xs->next->t, 7.0));
	erase_intersections(&xs);
	free(s);
}

Test(spheres, intersect_a_translated_sphere_with_a_ray)
{
	t_ray			r;
	t_sphere		*s;
	t_intersection	*xs;

	r = new_ray(point(0, 0, -5), vector(0, 0, 1));
	s = sphere_stub();
	set_transform(s, translation(5, 0, 0));
	xs = intersect(s, r);
	cr_assert(eq(ptr, xs, NULL));
	erase_intersections(&xs);
	free(s);
}

/*	Checks the normal on a sphere at a point on the x axis */
Test(spheres, normal_at_x_axis)
{
	t_sphere	*s;
	t_vector	n;
	t_tuple		res;

	s = sphere_stub();
	n = normal_at(*s, point(1, 0, 0));
	res = vector(1, 0, 0);

	cr_assert(eq(flt, n.x, res.x));
	cr_assert(eq(flt, n.y, res.y));
	cr_assert(eq(flt, n.z, res.z));
	cr_assert(eq(flt, n.w, res.w));
	free(s);
}

/*	Checks the normal on a sphere at a point on the y axis */
Test(spheres, normal_at_y_axis)
{
	t_sphere	*s;
	t_vector	n;
	t_tuple		res;

	s = sphere_stub();
	n = normal_at(*s, point(0, 1, 0));
	res = vector(0, 1, 0);

	cr_assert(eq(flt, n.x, res.x));
	cr_assert(eq(flt, n.y, res.y));
	cr_assert(eq(flt, n.z, res.z));
	cr_assert(eq(flt, n.w, res.w));
	free(s);
}

/*	Checks the normal on a sphere at a point on the z axis */
Test(spheres, normal_at_z_axis)
{
	t_sphere	*s;
	t_vector	n;
	t_tuple		res;

	s = sphere_stub();
	n = normal_at(*s, point(0, 0, 1));
	res = vector(0, 0, 1);

	cr_assert(eq(flt, n.x, res.x));
	cr_assert(eq(flt, n.y, res.y));
	cr_assert(eq(flt, n.z, res.z));
	cr_assert(eq(flt, n.w, res.w));
	free(s);
}

/*	Checks the normal on a sphere at a nonaxial point */
/*	IMPORTANT NOTE: maybe convertion to double is needed */
Test(spheres, normal_at_nonaxial_pt)
{
	t_sphere	*s;
	t_vector	n;
	t_tuple		res;
	float		coord;

	s = sphere_stub();
	coord = sqrtf(3.0)/3.0;
	n = normal_at(*s, point(coord, coord, coord));
	res = vector(coord, coord, coord);

	cr_assert_float_eq(n.x, res.x, EPSILON);
	cr_assert_float_eq(n.y, res.y, EPSILON);
	cr_assert_float_eq(n.z, res.z, EPSILON);
	cr_assert_float_eq(n.w, res.w, EPSILON);
	free(s);
}

/**
 *	Checks the feature of a normal vector which states
 *	that surface/normal vector should always be normalized.
 *	Refer to the book TRTC on p.78
 */
Test(spheres, normal_is_normalized_vector)
{
	t_sphere	*s;
	t_vector	n;
	t_tuple		res;
	float		coord;

	s = sphere_stub();
	coord = sqrtf(3.0)/3.0;
	n = normal_at(*s, point(coord, coord, coord));
	res = normalize(n);

	cr_assert_float_eq(n.x, res.x, EPSILON);
	cr_assert_float_eq(n.y, res.y, EPSILON);
	cr_assert_float_eq(n.z, res.z, EPSILON);
	cr_assert_float_eq(n.w, res.w, EPSILON);
	free(s);
}

/**	
 *	Checks the normal/surface vector when the sphere's
 *	origin is not longer at the world origin.
 */
Test(spheres, normal_on_a_translated_sphere)
{
	t_sphere	*s;
	t_vector	n;
	t_tuple		res;

	s = sphere_stub();
	set_transform(s, translation(0.0, 1.0, 0.0));
	n = normal_at(*s, point(0, 1.70711, -0.70711));
	res = vector(0, 0.70711, -0.70711);

	cr_assert_float_eq(n.x, res.x, EPSILON);
	cr_assert_float_eq(n.y, res.y, EPSILON);
	cr_assert_float_eq(n.z, res.z, EPSILON);
	cr_assert_float_eq(n.w, res.w, EPSILON);
	free(s);
}

/**	
 *	Checks the normal/surface vector when the sphere's
 *	origin is not longer at the world origin.
 */
Test(spheres, normal_on_a_transformed_sphere)
{
	t_sphere	*s;
	t_vector	n;
	t_matrix	m;
	t_tuple		res;
	float		coord;

	s = sphere_stub();
	m = multiply_mx_mx(scaling(1, 0.5, 1), \
			rotation_z((float) M_PI/5.0));
	set_transform(s, m);
	coord = sqrtf(2)/2.0;
	n = normal_at(*s, point(0, coord, -coord));
	res = vector(0, 0.97014, -0.24254);
	cr_assert_float_eq(n.x, res.x, EPSILON);
	cr_assert_float_eq(n.y, res.y, EPSILON);
	cr_assert_float_eq(n.z, res.z, EPSILON);
	cr_assert_float_eq(n.w, res.w, EPSILON);
	free(s);
}

/*	Checks if the default values of a sphere instance */
Test(spheres, sphere_default_material)
{
	t_sphere	*s;
	t_material	m;

	s = sphere_stub();
	m = material();
	m.ambient = 1;
	s->material = m;

	cr_assert(eq(flt, s->material.ambient, m.ambient));
	cr_assert(eq(flt, s->material.diffuse, m.diffuse));
	cr_assert(eq(flt, s->material.specular, m.specular));
	cr_assert(eq(flt, s->material.shininess, m.shininess));
	free(s);
}
