/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_spheres.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 09:22:45 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/06 10:47:08 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "shapes.h"
#include "utils.h"

Test(spheres, a_ray_intersect_a_sphere_at_two_points)
{
	t_ray			ray;
	t_sphere		sphere;
	t_intersection	*xs;

	ray = new_ray(point(0, 0, -5), vector(0, 0, 1));
	sphere = sphere_stub();
	xs = intersect(sphere, ray);
	cr_assert(eq(flt, xs->t, 4));
	cr_assert(eq(flt, xs->next->t, 6));
	erase_intersections(&xs);
}

Test(spheres, a_ray_intersects_a_sphere_at_a_tangent)
{
	t_ray			ray;
	t_sphere		sphere;
	t_intersection	*xs;

	ray = new_ray(point(0, 1, -5), vector(0, 0, 1));
	sphere = sphere_stub();
	xs = intersect(sphere, ray);
	cr_assert(eq(flt, xs->t, 5));
	cr_assert(eq(flt, xs->next->t, 5));
	erase_intersections(&xs);
}

Test(spheres, a_ray_misses_a_sphere)
{
	t_ray			ray;
	t_sphere		sphere;
	t_intersection	*xs;

	ray = new_ray(point(0, 2, -5), vector(0, 0, 1));
	sphere = sphere_stub();
	xs = intersect(sphere, ray);
	cr_assert(eq(ptr, xs, NULL));
	erase_intersections(&xs);
}

Test(spheres, a_ray_originates_inside_a_sphere)
{
	t_ray			ray;
	t_sphere		sphere;
	t_intersection	*xs;

	ray = new_ray(point(0, 0, 0), vector(0, 0, 1));
	sphere = sphere_stub();
	xs = intersect(sphere, ray);

	cr_assert(eq(i32, intersection_count(xs), 2));
	cr_assert(eq(flt, xs->t, -1));
	cr_assert(eq(flt, xs->next->t, 1));
	erase_intersections(&xs);
}

Test(spheres, a_sphere_is_behind_a_ray)
{
	t_ray			ray;
	t_sphere		sphere;
	t_intersection	*xs;

	ray = new_ray(point(0, 0, 5), vector(0, 0, 1));
	sphere = sphere_stub();
	xs = intersect(sphere, ray);
	cr_assert(eq(i32, intersection_count(xs), 2));
	cr_assert(eq(flt, xs->t, -6));
	cr_assert(eq(flt, xs->next->t, -4));
	erase_intersections(&xs);
}

Test(spheres, intersect_sets_the_object_on_the_intersection)
{
	t_ray			ray;
	t_sphere		sphere;
	t_intersection	*xs;

	xs = NULL;
	ray = new_ray(point(0, 0, -5), vector(0, 0, 1));
	sphere = sphere_stub();
	xs = intersect(sphere, ray);
	cr_assert(eq(i32, intersection_count(xs), 2));
	cr_assert(eq(i32, compare_spheres(xs->object.sphere, sphere), TRUE));
	cr_assert(eq(i32, compare_spheres(xs->object.sphere, sphere), TRUE));
	erase_intersections(&xs);
}

Test(spheres, a_spheres_default_transformation)
{
	t_sphere	sphere;

	sphere = sphere_stub();
	cr_assert(eq(
		i32,
		compare_matrix(sphere.transform, get_identity_matrix()), 0)
	);
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
	t_sphere		s;
	t_intersection	*xs;

	r = new_ray(point(0, 0, -5), vector(0, 0, 1));
	s = sphere_stub();
	set_transform(&s, scaling(2, 2, 2));
	xs = intersect(s, r);
	cr_assert(eq(flt, xs->t, 3.0));
	cr_assert(eq(flt, xs->next->t, 7.0));
	erase_intersections(&xs);
}

Test(spheres, intersect_a_translated_sphere_with_a_ray)
{
	t_ray			r;
	t_sphere		s;
	t_intersection	*xs;

	r = new_ray(point(0, 0, -5), vector(0, 0, 1));
	s = sphere_stub();
	set_transform(&s, translation(5, 0, 0));
	xs = intersect(s, r);
	cr_assert(eq(ptr, xs, NULL));
	erase_intersections(&xs);
}
