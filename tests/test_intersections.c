/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_intersections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 09:28:46 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/22 14:10:41 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"
#include "utils.h"

/*
 * This test checks if the intersection returned by the "intersection"
 * function correctly encapsulates the value of "t" and the object of
 * the spherical shape.
 */
Test(intersections, an_intersection_encapsulates_t_and_object)
{
	t_shape	shape;
	t_hit	*i;

	shape = new_sphere();
	i = intersection(3.5, &shape);

	cr_assert(eq(flt, i->t, 3.5));
	cr_assert(eq(flt, i->object->sphere.radius, shape.sphere.radius));
}

/*
 * This test checks if the function "insert_intersection" correctly aggregates
 * two intersections into a list of intersections. The test creates two spheres
 * and two intersections, inserts them into the list, and checks if the list
 * contains the expected intersections.
 */
Test(intersections, aggregating_intersections)
{
	t_shape	s1;
	t_shape	s2;
	t_hit	*i1;
	t_hit	*i2;
	t_hit	*xs;

	xs = NULL;
	s1 = new_sphere();
	s2 = new_sphere();
	i1 = intersection(1, &s1);
	i2 = intersection(2, &s2);

	insert_intersection(&xs, i1);
	insert_intersection(&xs, i2);

	cr_assert(eq(flt, xs->t, 1));
	cr_assert(eq(flt, xs->next->t, 2));
}

/*
 * This test checks if the function "visible_hit" correctly returns the first
 * visible intersection from a list of intersections when all intersections
 * have positive "t" values. The test creates two spheres and two intersections,
 * inserts them into the list, and checks if the function returns the expected
 * intersection.
 */
Test(intersections, hit_when_all_intersections_have_positive_t)
{
	t_shape	s1;
	t_shape	s2;
	t_hit	*xs;
	t_hit	*i;

	xs = NULL;
	s1 = new_sphere();
	s2 = new_sphere();
	insert_intersection(&xs, intersection(1, &s1));
	insert_intersection(&xs, intersection(2, &s2));

	i = hit(xs);
	cr_assert(eq(i32, intersection_count(xs), 2));
	cr_assert(eq(i32, compare_spheres(&i->object[0].sphere, &s1.sphere), TRUE));
}

/*
 * This test checks if the function "visible_hit" correctly returns NULL when
 * all intersections in the list have negative "t" values. The test creates a
 * sphere and two intersections with negative "t" values, inserts them into the
 * list, and checks if the function returns NULL as expected.
 */
Test(intersections, hit_when_all_intersections_have_negative_t)
{
	t_shape	shape;
	t_hit	*xs;
	t_hit	*expected;

	xs = NULL;
	shape = new_sphere();
	insert_intersection(&xs, intersection(-2, &shape));
	insert_intersection(&xs, intersection(-3, &shape));

	expected = hit(xs);
	cr_assert(eq(i32, intersection_count(xs), 2));
	cr_assert(eq(ptr, expected, NULL));
}

/*
 * This test checks if the function "visible_hit" correctly returns the lowest
 * non-negative intersection from a list of intersections. The test creates a
 * sphere and four intersections with different "t" values, inserts them into
 * the list, and checks if the function returns the expected intersection.
 */
Test(intersections, the_hit_is_always_the_lowest_nonnegative_intersection)
{
	t_shape	shape;
	t_hit	*xs;
	t_hit	*i;

	xs = NULL;
	shape = new_sphere();
	insert_intersection(&xs, intersection(5, &shape));
	insert_intersection(&xs, intersection(7, &shape));
	insert_intersection(&xs, intersection(-3, &shape));
	insert_intersection(&xs, intersection(2, &shape));

	i = hit(xs);
	cr_assert(eq(i32, intersection_count(xs), 4));
	cr_assert(eq(flt, i->t, 2));
}

/* The hit should offset the point */
Test(intersections, hit_should_offset_point)
{
	t_ray		r;
	t_shape		shape;
	t_hit		*i;
	t_comps		comps;

	r = new_ray(point(0, 0, -5), vector(0, 0, 1));
	shape = new_sphere();
	set_transform(&shape, translation(0, 0, 1));
	i = intersection(5, &shape);
	comps = prepare_computations(i, r);

	//comps.over_point.z < -EPSILON/2
	cr_assert(lt(flt, comps.over_point.z, -EPSILON/2));
	//comps.point.z > comps.over_point.z
	cr_assert(gt(flt, comps.point.z, comps.over_point.z));
}
