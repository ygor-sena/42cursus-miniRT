/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:19:07 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/09 15:41:45 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
 * This test checks if the function "new_ray" correctly creates a new ray with
 * the given origin and direction.
 */
Test(rays, creating_a_new_ray)
{
	t_ray		ray;
	t_point		origin;
	t_vector	direction;

	origin = point(1, 2, 3);
	direction = vector(4, 5, 6);
	ray = new_ray(origin, direction);
	cr_assert(eq(flt, ray.origin.x, origin.x));
	cr_assert(eq(flt, ray.origin.y, origin.y));
	cr_assert(eq(flt, ray.origin.z, origin.z));
	cr_assert(eq(flt, ray.origin.w, origin.w));
}

/*
 * This test checks if the function "position" correctly computes a point along
 * a ray at a given distance from the origin.
 */
Test(rays, computing_a_point_from_distance)
{
	t_ray	ray;
	t_point	result;
	t_point	expected;

	ray = new_ray(point(2, 3, 4), vector(1, 0, 0));
	result = position(ray, 0);
	expected = point(2, 3, 4);
	cr_assert(eq(flt, result.x, expected.x));
	cr_assert(eq(flt, result.y, expected.y));
	cr_assert(eq(flt, result.z, expected.z));
	cr_assert(eq(flt, result.w, expected.w));

	result = position(ray, 1);
	expected = point(3, 3, 4);
	cr_assert(eq(flt, result.x, expected.x));
	cr_assert(eq(flt, result.y, expected.y));
	cr_assert(eq(flt, result.z, expected.z));
	cr_assert(eq(flt, result.w, expected.w));

	expected = point(1, 3, 4);
	result = position(ray, -1);
	cr_assert(eq(flt, result.x, expected.x));
	cr_assert(eq(flt, result.y, expected.y));
	cr_assert(eq(flt, result.z, expected.z));
	cr_assert(eq(flt, result.w, expected.w));

	result = position(ray, 2.5);
	expected = point(4.5, 3, 4);
	cr_assert(eq(flt, result.x, expected.x));
	cr_assert(eq(flt, result.y, expected.y));
	cr_assert(eq(flt, result.z, expected.z));
	cr_assert(eq(flt, result.w, expected.w));
}

/*
 * This test checks if the function "transform" correctly translates a ray by a
 * given matrix.
 */
Test(rays, translating_a_ray)
{
	t_ray		ray;
	t_ray		ray2;
	t_matrix	matrix;

	ray = new_ray(point(1, 2, 3), vector(0, 1, 0));
	matrix = translation(3, 4, 5);
	ray2 = transform(ray, matrix);
	cr_assert(eq(flt, ray2.origin.x, 4));
	cr_assert(eq(flt, ray2.origin.y, 6));
	cr_assert(eq(flt, ray2.origin.z, 8));
}

/*
 * This test checks if the function "transform" correctly scales a ray by a
 * given matrix.
 */
Test(rays, scaling_a_ray)
{
	t_ray		ray;
	t_ray		ray2;
	t_matrix	matrix;

	ray = new_ray(point(1, 2, 3), vector(0, 1, 0));
	matrix = scaling(2, 3, 4);
	ray2 = transform(ray, matrix);

	cr_assert(eq(flt, ray2.origin.x, 2));
	cr_assert(eq(flt, ray2.origin.y, 6));
	cr_assert(eq(flt, ray2.origin.z, 12));
}
