/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cones.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 09:38:52 by yde-goes          #+#    #+#             */
/*   Updated: 2023/05/16 22:21:08 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

// Intersecting a cone with a ray
Test(cones, intersect_cone_with_ray_1)
{
	t_shape	shape;
	t_tuple	origin;
	t_tuple	direction;
	t_ray	r;
	t_hit	*xs;
	
	xs = NULL;
	shape = new_cone();
	origin = point(0, 0, -5);
	direction = normalize(vector(0, 0, 1));
	r = new_ray(origin, direction);
	intersect_cone(&xs, &shape, r);
	
	cr_assert(eq(i32, intersection_count(xs), 2));
	cr_assert(eq(flt, xs->t, 5));
	cr_assert(eq(flt, xs->next->t, 5));
}

Test(cones, intersect_cone_with_ray_2)
{
	t_shape	shape;
	t_tuple	origin;
	t_tuple	direction;
	t_ray	r;
	t_hit	*xs;
	
	xs = NULL;
	shape = new_cone();
	origin = point(0, 0, -5);
	direction = normalize(vector(1, 1, 1));
	r = new_ray(origin, direction);
	intersect_cone(&xs, &shape, r);
	
	cr_assert(eq(i32, intersection_count(xs), 2));
	cr_assert(eq(flt, xs->t, 8.66025));
	cr_assert_float_eq(xs->t, 8.66025, EPSILON);
	cr_assert_float_eq(xs->next->t, 8.66025, EPSILON);
}

Test(cones, intersect_cone_with_ray_3)
{
	t_shape	shape;
	t_tuple	origin;
	t_tuple	direction;
	t_ray	r;
	t_hit	*xs;
	
	xs = NULL;
	shape = new_cone();
	origin = point(1, 1, -5);
	direction = normalize(vector(-0.5, -1, 1));
	r = new_ray(origin, direction);
	intersect_cone(&xs, &shape, r);
	
	cr_assert(eq(i32, intersection_count(xs), 2));
	//cr_assert(eq(flt, xs->t, 4.55006));
	cr_assert_float_eq(xs->t, 4.55006, EPSILON);
	cr_assert(eq(flt, xs->t, 49.44994));
	cr_assert_float_eq(xs->next->t, 49.44994, EPSILON);
}

//Intersecting a cone with a ray parallel to one of its halves
Test(cones, intersect_cone_ray_parallel_to_one_half)
{
	t_shape	shape;
	t_tuple	origin;
	t_tuple	direction;
	t_ray	r;
	t_hit	*xs;
	
	xs = NULL;
	shape = new_cone();
	origin = point(0, 0, -1);
	direction = normalize(vector(0, 1, 1));
	r = new_ray(origin, direction);
	intersect_cone(&xs, &shape, r);
	
	cr_assert(eq(i32, intersection_count(xs), 1));
	cr_assert_float_eq(xs->t, 0.35355, EPSILON);
}

//Intersecting a cone's end caps
Test(cones, intersect_a_cone_end_caps_1)
{
	t_shape	shape;
	t_tuple	origin;
	t_tuple	direction;
	t_ray	r;
	t_hit	*xs;
	
	xs = NULL;
	shape = new_cone();
	shape.cone.minimum = -0.5;
	shape.cone.maximum = 0.5;
	shape.cone.closed = TRUE;
	origin = point(0, 0, -5);
	direction = normalize(vector(0, 1, 0));
	r = new_ray(origin, direction);
	intersect_cone(&xs, &shape, r);
	
	cr_assert(eq(ptr, xs, NULL));
	cr_assert(eq(i32, intersection_count(xs), 0));
}

Test(cones, intersect_a_cone_end_caps_2)
{
	t_shape	shape;
	t_tuple	origin;
	t_tuple	direction;
	t_ray	r;
	t_hit	*xs;
	
	xs = NULL;
	shape = new_cone();
	shape.cone.minimum = -0.5;
	shape.cone.maximum = 0.5;
	shape.cone.closed = TRUE;
	origin = point(0, 0, -0.25);
	direction = normalize(vector(0, 1, 1));
	r = new_ray(origin, direction);
	intersect_cone(&xs, &shape, r);
	
	cr_assert(eq(i32, intersection_count(xs), 2));
}

Test(cones, intersect_a_cone_end_caps_3)
{
	t_shape	shape;
	t_tuple	origin;
	t_tuple	direction;
	t_ray	r;
	t_hit	*xs;
	
	xs = NULL;
	shape = new_cone();
	shape.cone.minimum = -0.5;
	shape.cone.maximum = 0.5;
	shape.cone.closed = TRUE;
	origin = point(0, 0, -0.25);
	direction = normalize(vector(0, 1, 0));
	r = new_ray(origin, direction);
	intersect_cone(&xs, &shape, r);
	
	cr_assert(eq(i32, intersection_count(xs), 4));
}

//Computing the normal vector on a cone
Test(cones, computing_normal_vector_cone_1)
{
	t_shape	shape;
	t_tuple	n;
	t_tuple	res;

	shape = new_cone();
	n = normal_at_cone(&shape, point(0, 0, 0));
	res = vector(0, 0, 0);
	
	cr_assert_float_eq(n.x, res.x, EPSILON);
	cr_assert_float_eq(n.y, res.y, EPSILON);
	cr_assert_float_eq(n.z, res.z, EPSILON);
	cr_assert_float_eq(n.w, res.w, EPSILON);
}

Test(cones, computing_normal_vector_cone_2)
{
	t_shape	shape;
	t_tuple	n;
	t_tuple	res;

	shape = new_cone();
	n = normal_at_cone(&shape, point(1, 1, 1));
	res = vector(1, -sqrtf(2), 1);
	
	cr_assert_float_eq(n.x, res.x, EPSILON);
	cr_assert_float_eq(n.y, res.y, EPSILON);
	cr_assert_float_eq(n.z, res.z, EPSILON);
	cr_assert_float_eq(n.w, res.w, EPSILON);
}

Test(cones, computing_normal_vector_cone_3)
{
	t_shape	shape;
	t_tuple	n;
	t_tuple	res;

	shape = new_cone();
	n = normal_at_cone(&shape, point(-1, -1, 0));
	res = vector(-1, 1, 0);
	
	cr_assert_float_eq(n.x, res.x, EPSILON);
	cr_assert_float_eq(n.y, res.y, EPSILON);
	cr_assert_float_eq(n.z, res.z, EPSILON);
	cr_assert_float_eq(n.w, res.w, EPSILON);
}
