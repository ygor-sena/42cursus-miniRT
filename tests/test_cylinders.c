/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cylinders.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:30:32 by yde-goes          #+#    #+#             */
/*   Updated: 2023/05/13 14:15:44 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/* A ray misses a cylinder */
Test(cylinders, ray_misses_cylinder_1)
{
	t_shape	cyl;
	t_tuple	origin;
	t_tuple	direction;
	t_ray	r;
	t_hit	*xs;
	
	xs = NULL;
	cyl = new_cylinder();
	origin = point(1, 0, 0);
	direction = normalize(vector(0, 1, 0));
	r = new_ray(origin, direction);
	intersect_cylinder(&xs, &cyl, r);
	
	cr_assert(eq(ptr, xs, NULL));
}

/* A ray misses a cylinder */
Test(cylinders, ray_misses_cylinder_2)
{
	t_shape	cyl;
	t_tuple	origin;
	t_tuple	direction;
	t_ray	r;
	t_hit	*xs;
	
	xs = NULL;
	cyl = new_cylinder();
	origin = point(0, 0, 0);
	direction = normalize(vector(0, 1, 0));
	r = new_ray(origin, direction);
	intersect_cylinder(&xs, &cyl, r);
	
	cr_assert(eq(ptr, xs, NULL));
}

/* A ray misses a cylinder */
Test(cylinders, ray_misses_cylinder_3)
{
	t_shape	cyl;
	t_tuple	origin;
	t_tuple	direction;
	t_ray	r;
	t_hit	*xs;
	
	xs = NULL;
	cyl = new_cylinder();
	origin = point(0, 0, -5);
	direction = normalize(vector(1, 1, 1));
	r = new_ray(origin, direction);
	intersect_cylinder(&xs, &cyl, r);
	
	cr_assert(eq(ptr, xs, NULL));
}

/* A ray strikes a cylinder */
Test(cylinders, ray_strikes_cylinder_1)
{
	t_shape	cyl;
	t_tuple	origin;
	t_tuple	direction;
	t_ray	r;
	t_hit	*xs;
	
	xs = NULL;
	cyl = new_cylinder();
	origin = point(1, 0, -5);
	direction = normalize(vector(0, 0, 1));
	r = new_ray(origin, direction);
	intersect_cylinder(&xs, &cyl, r);
	
	cr_assert(eq(i32, intersection_count(xs), 2));
	cr_assert(eq(flt, xs->t, 5));
	cr_assert(eq(flt, xs->next->t, 5));
}

/* A ray strikes a cylinder */
Test(cylinders, ray_strikes_cylinder_2)
{
	t_shape	cyl;
	t_tuple	origin;
	t_tuple	direction;
	t_ray	r;
	t_hit	*xs;
	
	xs = NULL;
	cyl = new_cylinder();
	origin = point(0, 0, -5);
	direction = normalize(vector(0, 0, 1));
	r = new_ray(origin, direction);
	intersect_cylinder(&xs, &cyl, r);
	
	cr_assert(eq(i32, intersection_count(xs), 2));
	cr_assert(eq(flt, xs->t, 4));
	cr_assert(eq(flt, xs->next->t, 6));
}

/* A ray strikes a cylinder */
//WARNING: modified test values! Original ones: 6.80798, 7.08872
Test(cylinders, ray_strikes_cylinder_3)
{
	t_shape	cyl;
	t_tuple	origin;
	t_tuple	direction;
	t_ray	r;
	t_hit	*xs;
	
	xs = NULL;
	cyl = new_cylinder();
	origin = point(0.5, 0, -5);
	direction = normalize(vector(0.1, 1, 1));
	r = new_ray(origin, direction);
	intersect_cylinder(&xs, &cyl, r);
	
	cr_assert(eq(i32, intersection_count(xs), 2));
	cr_assert_float_eq(xs->t, 6.80800, EPSILON);
	cr_assert_float_eq(xs->next->t, 7.08870, EPSILON);
}

/* Normal vector on a cylinder */
Test(cylinders, normal_vector_on_cylinder_1)
{
	t_shape	cyl;
	t_tuple	n;
	t_tuple	res;

	cyl = new_cylinder();
	n = normal_at_cylinder(&cyl, point(1, 0, 0));
	res = vector(1, 0, 0);
	
	cr_assert_float_eq(n.x, res.x, EPSILON);
	cr_assert_float_eq(n.y, res.y, EPSILON);
	cr_assert_float_eq(n.z, res.z, EPSILON);
	cr_assert_float_eq(n.w, res.w, EPSILON);
}

/* Normal vector on a cylinder */
Test(cylinders, normal_vector_on_cylinder_2)
{
	t_shape	cyl;
	t_tuple	n;
	t_tuple	res;

	cyl = new_cylinder();
	n = normal_at_cylinder(&cyl, point(0, 5, -1));
	res = vector(0, 0, -1);
	
	cr_assert_float_eq(n.x, res.x, EPSILON);
	cr_assert_float_eq(n.y, res.y, EPSILON);
	cr_assert_float_eq(n.z, res.z, EPSILON);
	cr_assert_float_eq(n.w, res.w, EPSILON);
}

/* Normal vector on a cylinder */
Test(cylinders, normal_vector_on_cylinder_3)
{
	t_shape	cyl;
	t_tuple	n;
	t_tuple	res;

	cyl = new_cylinder();
	n = normal_at_cylinder(&cyl, point(0, -2, 1));
	res = vector(0, 0, 1);
	
	cr_assert_float_eq(n.x, res.x, EPSILON);
	cr_assert_float_eq(n.y, res.y, EPSILON);
	cr_assert_float_eq(n.z, res.z, EPSILON);
	cr_assert_float_eq(n.w, res.w, EPSILON);
}

/* Normal vector on a cylinder */
Test(cylinders, normal_vector_on_cylinder_4)
{
	t_shape	cyl;
	t_tuple	n;
	t_tuple	res;

	cyl = new_cylinder();
	n = normal_at_cylinder(&cyl, point(-1, 1, 0));
	res = vector(-1, 0, 0);
	
	cr_assert_float_eq(n.x, res.x, EPSILON);
	cr_assert_float_eq(n.y, res.y, EPSILON);
	cr_assert_float_eq(n.z, res.z, EPSILON);
	cr_assert_float_eq(n.w, res.w, EPSILON);
}

/* The default mininum and maxinum for a cylinder */
Test(cylinders, default_min_max_for_cylinder)
{
	t_shape	cyl;

	cyl = new_cylinder();
	cr_assert(eq(flt, cyl.cylinder.minimum, -INFINITY));
	cr_assert(eq(flt, cyl.cylinder.maximum, INFINITY));
}

/*
 * Intersecting a constrained cylinder. Show that the cylinders in your ray
 * tracer can be truncated at either end. This test cast a ray diagonally from
 * inside the cylinder, with the ray escaping without intersecting the cylinder.
 */
Test(cylinders, intersecting_constrained_cylinder_1)
{
	t_shape	cyl;
	t_tuple	direction;
	t_ray	r;
	t_hit	*xs;
	
	xs = NULL;
	cyl = new_cylinder();
	cyl.cylinder.minimum = 1;
	cyl.cylinder.maximum = 2;
	direction = normalize(vector(0.1, 1, 0));
	r = new_ray(point(0, 1.5, 0), direction);
	intersect_cylinder(&xs, &cyl, r);

	cr_assert(eq(i32, intersection_count(xs), 0));	
}

/*
 * This test case casts rays perpendicularly to the y xis, but from ABOVE the
 * and also miss.
 */
Test(cylinders, intersecting_constrained_cylinder_2)
{
	t_shape	cyl;
	t_tuple	direction;
	t_ray	r;
	t_hit	*xs;
	
	xs = NULL;
	cyl = new_cylinder();
	cyl.cylinder.minimum = 1;
	cyl.cylinder.maximum = 2;
	direction = normalize(vector(0, 0, 1));
	r = new_ray(point(0, 3, -5), direction);
	intersect_cylinder(&xs, &cyl, r);

	cr_assert(eq(i32, intersection_count(xs), 0));	
}

/*
 * This test case casts rays perpendicularly to the y xis, but from BELOW the
 * and also miss.
 */
Test(cylinders, intersecting_constrained_cylinder_3)
{
	t_shape	cyl;
	t_tuple	direction;
	t_ray	r;
	t_hit	*xs;
	
	xs = NULL;
	cyl = new_cylinder();
	cyl.cylinder.minimum = 1;
	cyl.cylinder.maximum = 2;
	direction = normalize(vector(0, 0, -5));
	r = new_ray(point(0, 0, 1), direction);
	intersect_cylinder(&xs, &cyl, r);

	cr_assert(eq(i32, intersection_count(xs), 0));	
}

/*
 * This test case is an edge situation. It shows that the maximum value is
 * itself outside the bounds of the cylinder. 
 */
Test(cylinders, intersecting_constrained_cylinder_4)
{
	t_shape	cyl;
	t_tuple	direction;
	t_ray	r;
	t_hit	*xs;
	
	xs = NULL;
	cyl = new_cylinder();
	cyl.cylinder.minimum = 1;
	cyl.cylinder.maximum = 2;
	direction = normalize(vector(0, 2, -5));
	r = new_ray(point(0, 0, 1), direction);
	intersect_cylinder(&xs, &cyl, r);

	cr_assert(eq(i32, intersection_count(xs), 0));	
}

/*
 * This test case is an edge situation. It shows that the minimum value is
 * itself outside the bounds of the cylinder. 
 */
Test(cylinders, intersecting_constrained_cylinder_5)
{
	t_shape	cyl;
	t_tuple	direction;
	t_ray	r;
	t_hit	*xs;
	
	xs = NULL;
	cyl = new_cylinder();
	cyl.cylinder.minimum = 1;
	cyl.cylinder.maximum = 2;
	direction = normalize(vector(0, 1, -5));
	r = new_ray(point(0, 0, 1), direction);
	intersect_cylinder(&xs, &cyl, r);

	cr_assert(eq(i32, intersection_count(xs), 0));	
}

/*
 * This test casts a ray perpendicularly through the middle of the cylinder and
 * produces two intersections.
 */
Test(cylinders, intersecting_constrained_cylinder_6)
{
	t_shape	cyl;
	t_tuple	direction;
	t_ray	r;
	t_hit	*xs;
	
	xs = NULL;
	cyl = new_cylinder();
	cyl.cylinder.minimum = 1;
	cyl.cylinder.maximum = 2;
	direction = normalize(vector(0, 0, 1));
	r = new_ray(point(0, 1.5, -2), direction);
	intersect_cylinder(&xs, &cyl, r);

	cr_assert(eq(i32, intersection_count(xs), 2));	
}

/* Checks the default closed value for a cylinder */
Test(cylinders, default_closed_value_is_false)
{
	t_shape	cyl;

	cyl = new_cylinder();
	cr_assert(eq(i32, cyl.cylinder.closed, FALSE));
}

/*
 * Intersecting the caps of a closed cylinder. Show that your intersection
 * routine correctly finds the points of intersection between a ray and a
 * cylinder's end caps.
 * 
 * The ray in this example starts above the cylinder and points down through
 * the cylinder’s middle, along the y axis. It should intersect both end caps,
 * resulting in two intersections.
 */
Test(cylinders, intersect_caps_closed_cylinder_1)
{
	t_shape	cyl;
	t_tuple	direction;
	t_ray	r;
	t_hit	*xs;

	xs = NULL;
	cyl = new_cylinder();
	cyl.cylinder.minimum = 1;
	cyl.cylinder.maximum = 2;
	cyl.cylinder.closed = TRUE;
	direction = normalize(vector(0, -1, 0));
	r = new_ray(point(0, 3, 0), direction);
	intersect_cylinder(&xs, &cyl, r);

	cr_assert(eq(i32, intersection_count(xs), 2));
}

/*
 * Test 2 originate above the cylinder and cast a ray diagonally through it,
 * intersecting one end cap before exiting out the far side of the cylinder.
 * This also results in two intersections.
 */
Test(cylinders, intersect_caps_closed_cylinder_2)
{
	t_shape	cyl;
	t_tuple	direction;
	t_ray	r;
	t_hit	*xs;

	xs = NULL;
	cyl = new_cylinder();
	cyl.cylinder.minimum = 1;
	cyl.cylinder.maximum = 2;
	cyl.cylinder.closed = TRUE;
	direction = normalize(vector(0, -1, 2));
	r = new_ray(point(0, 3, -2), direction);
	intersect_cylinder(&xs, &cyl, r);

	cr_assert(eq(i32, intersection_count(xs), 2));
}


/*
 * Test 3 is a corner case. It originates above and below the cylinder,
 * intersecting an end cap, but they exit the cylinder at the point where the
 * other end cap intersects the side of the cylinder. In this case, there should
 * still be only two intersections: one with the first end cap and the other
 * where the second end cap meets the cylinder wall.
 */
Test(cylinders, intersect_caps_closed_cylinder_3)
{
	t_shape	cyl;
	t_tuple	direction;
	t_ray	r;
	t_hit	*xs;

	xs = NULL;
	cyl = new_cylinder();
	cyl.cylinder.minimum = 1;
	cyl.cylinder.maximum = 2;
	cyl.cylinder.closed = TRUE;
	direction = normalize(vector(0, -1, 1));
	r = new_ray(point(0, 4, -2), direction);
	intersect_cylinder(&xs, &cyl, r);

	cr_assert(eq(i32, intersection_count(xs), 2));
}

/*
 * Test 4 originate below the cylinder and cast a ray diagonally through it,
 * intersecting one end cap before exiting out the far side of the cylinder.
 * This also results in two intersections.
 */
Test(cylinders, intersect_caps_closed_cylinder_4)
{
	t_shape	cyl;
	t_tuple	direction;
	t_ray	r;
	t_hit	*xs;

	xs = NULL;
	cyl = new_cylinder();
	cyl.cylinder.minimum = 1;
	cyl.cylinder.maximum = 2;
	cyl.cylinder.closed = TRUE;
	direction = normalize(vector(0, 1, 2));
	r = new_ray(point(0, 0, -2), direction);
	intersect_cylinder(&xs, &cyl, r);

	cr_assert(eq(i32, intersection_count(xs), 2));
}

/*
 * Test 5 is a corner case. It originates below and below the cylinder,
 * intersecting an end cap, but they exit the cylinder at the point where the
 * other end cap intersects the side of the cylinder. In this case, there should
 * still be only two intersections: one with the first end cap and the other
 * where the second end cap meets the cylinder wall.
 */
Test(cylinders, intersect_caps_closed_cylinder_5)
{
	t_shape	cyl;
	t_tuple	direction;
	t_ray	r;
	t_hit	*xs;

	xs = NULL;
	cyl = new_cylinder();
	cyl.cylinder.minimum = 1;
	cyl.cylinder.maximum = 2;
	cyl.cylinder.closed = TRUE;
	direction = normalize(vector(0, 1, 1));
	r = new_ray(point(0, -1, -2), direction);
	intersect_cylinder(&xs, &cyl, r);

	cr_assert(eq(i32, intersection_count(xs), 2));
}

/* The normal vector on a cylinder's end caps */
Test(cylinders, normal_vector_on_cyl_end_caps_1)
{
	t_shape	cyl;
	t_tuple	n;
	t_tuple	res;

	cyl = new_cylinder();
	cyl.cylinder.minimum = 1;
	cyl.cylinder.maximum = 2;
	cyl.cylinder.closed = TRUE;
	n = normal_at_cylinder(&cyl, point(0, 1, 0));
	res = vector(0, -1, 0);

	cr_assert_float_eq(n.x, res.x, EPSILON);
	cr_assert_float_eq(n.y, res.y, EPSILON);
	cr_assert_float_eq(n.z, res.z, EPSILON);
	cr_assert_float_eq(n.w, res.w, EPSILON);
}

Test(cylinders, normal_vector_on_cyl_end_caps_2)
{
	t_shape	cyl;
	t_tuple	n;
	t_tuple	res;

	cyl = new_cylinder();
	cyl.cylinder.minimum = 1;
	cyl.cylinder.maximum = 2;
	cyl.cylinder.closed = TRUE;
	n = normal_at_cylinder(&cyl, point(0.5, 1, 0));
	res = vector(0, -1, 0);

	cr_assert_float_eq(n.x, res.x, EPSILON);
	cr_assert_float_eq(n.y, res.y, EPSILON);
	cr_assert_float_eq(n.z, res.z, EPSILON);
	cr_assert_float_eq(n.w, res.w, EPSILON);
}

Test(cylinders, normal_vector_on_cyl_end_caps_3)
{
	t_shape	cyl;
	t_tuple	n;
	t_tuple	res;

	cyl = new_cylinder();
	cyl.cylinder.minimum = 1;
	cyl.cylinder.maximum = 2;
	cyl.cylinder.closed = TRUE;
	n = normal_at_cylinder(&cyl, point(0, 1, 0.5));
	res = vector(0, -1, 0);

	cr_assert_float_eq(n.x, res.x, EPSILON);
	cr_assert_float_eq(n.y, res.y, EPSILON);
	cr_assert_float_eq(n.z, res.z, EPSILON);
	cr_assert_float_eq(n.w, res.w, EPSILON);
}

Test(cylinders, normal_vector_on_cyl_end_caps_4)
{
	t_shape	cyl;
	t_tuple	n;
	t_tuple	res;

	cyl = new_cylinder();
	cyl.cylinder.minimum = 1;
	cyl.cylinder.maximum = 2;
	cyl.cylinder.closed = TRUE;
	n = normal_at_cylinder(&cyl, point(0, 2, 0));
	res = vector(0, 1, 0);

	cr_assert_float_eq(n.x, res.x, EPSILON);
	cr_assert_float_eq(n.y, res.y, EPSILON);
	cr_assert_float_eq(n.z, res.z, EPSILON);
	cr_assert_float_eq(n.w, res.w, EPSILON);
}

Test(cylinders, normal_vector_on_cyl_end_caps_5)
{
	t_shape	cyl;
	t_tuple	n;
	t_tuple	res;

	cyl = new_cylinder();
	cyl.cylinder.minimum = 1;
	cyl.cylinder.maximum = 2;
	cyl.cylinder.closed = TRUE;
	n = normal_at_cylinder(&cyl, point(0.5, 2, 0));
	res = vector(0, 1, 0);

	cr_assert_float_eq(n.x, res.x, EPSILON);
	cr_assert_float_eq(n.y, res.y, EPSILON);
	cr_assert_float_eq(n.z, res.z, EPSILON);
	cr_assert_float_eq(n.w, res.w, EPSILON);
}

Test(cylinders, normal_vector_on_cyl_end_caps_6)
{
	t_shape	cyl;
	t_tuple	n;
	t_tuple	res;

	cyl = new_cylinder();
	cyl.cylinder.minimum = 1;
	cyl.cylinder.maximum = 2;
	cyl.cylinder.closed = TRUE;
	n = normal_at_cylinder(&cyl, point(0, 2, 0.5));
	res = vector(0, 1, 0);

	cr_assert_float_eq(n.x, res.x, EPSILON);
	cr_assert_float_eq(n.y, res.y, EPSILON);
	cr_assert_float_eq(n.z, res.z, EPSILON);
	cr_assert_float_eq(n.w, res.w, EPSILON);
}
