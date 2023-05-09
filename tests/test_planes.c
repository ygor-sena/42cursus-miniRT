/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_planes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:52:01 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/09 12:38:40 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/* The normal of a plane is constant everywhere */
Test(planes, constant_normal)
{
	t_shape		plane;
	t_vector	n1;
	t_vector	n2;
	t_vector	n3;

	plane = new_plane();
	n1 = normal_at_plane(&plane, point(0, 0, 0));
	n2 = normal_at_plane(&plane, point(10, 0, -10));
	n3 = normal_at_plane(&plane, point(-5, 0, 150));

	cr_assert(eq(flt, compare_tuples(n1, vector(0, 1, 0)), TRUE));
	cr_assert(eq(flt, compare_tuples(n2, vector(0, 1, 0)), TRUE));
	cr_assert(eq(flt, compare_tuples(n3, vector(0, 1, 0)), TRUE));
}

/* Intersect with a ray parallel to the plane */
Test(planes, intersect_a_ray_parallel)
{
	t_shape	p;
	t_ray	r;
	t_hit	*xs;

	xs = NULL;
	p = new_plane();
	r = new_ray(point(0, 10, 0), vector(0, 0, 1));
	intersect_plane(&xs, &p, r);

	cr_assert(eq(ptr, xs, NULL));
}

/* Intersect with a coplanar ray */
Test(planes, intersect_a_coplanar)
{
	t_shape	p;
	t_ray	r;
	t_hit	*xs;

	xs = NULL;
	p = new_plane();
	r = new_ray(point(0, 0, 0), vector(0, 0, 1));
	intersect_plane(&xs, &p, r);

	cr_assert(eq(ptr, xs, NULL));
}

/* A ray intersecting a plane from above */
Test(planes, intersect_from_above)
{
	t_shape	p;
	t_ray	r;
	t_hit	*xs;

	xs = NULL;
	p = new_plane();
	r = new_ray(point(0, 1, 0), vector(0, -1, 0));
	intersect_plane(&xs, &p, r);

	cr_assert(eq(flt, xs[0].t, 1));
	cr_assert(eq(ptr, xs[0].object, &p));
}

/* A ray intersecting a plane from below */
Test(planes, intersect_from_below)
{
	t_shape	p;
	t_ray	r;
	t_hit	*xs;

	xs = NULL;
	p = new_plane();
	r = new_ray(point(0, -1, 0), vector(0, 1, 0));
	intersect_plane(&xs, &p, r);

	cr_assert(eq(flt, xs[0].t, 1));
	cr_assert(eq(ptr, xs[0].object, &p));
}
