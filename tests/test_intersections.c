/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_intersections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 09:28:46 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/27 14:48:57 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

Test(intersections, an_intersection_encapsulates_t_and_object)
{
	t_shape	shape;
	t_hit	*i;

	shape = new_sphere();
	i = intersection(3.5, &shape);

	cr_assert(eq(flt, i->t, 3.5));
	cr_assert(eq(flt, i->object->sphere.radius, shape.sphere.radius));
}

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
