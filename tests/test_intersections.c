/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_intersections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 09:28:46 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/06 10:47:25 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "shapes.h"
#include "utils.h"

Test(intersections, an_intersection_encapsulates_t_and_object)
{
	t_sphere		sphere;
	t_intersection	*i;

	sphere = sphere_stub();
	i = intersection(3.5, sphere);
	cr_assert(eq(flt, i->t, 3.5));
	cr_assert(eq(flt, i->object.sphere.radius, sphere.radius));
}

Test(intersections, aggregating_intersections)
{
	t_intersection	*i1;
	t_intersection	*i2;
	t_intersection	*xs;

	xs = NULL;
	i1 = intersection(1, sphere_stub());
	i2 = intersection(2, sphere_stub());

	insert_intersection(&xs, i1);
	insert_intersection(&xs, i2);
	cr_assert(eq(flt, xs->t, 1));
	cr_assert(eq(flt, xs->next->t, 2));
	erase_intersections(&xs);
}

Test(intersections, hit_when_all_intersections_have_positive_t)
{
	t_sphere		sphere;
	t_intersection	*i1;
	t_intersection	*i2;
	t_intersection	*xs;
	t_intersection	*i;

	xs = NULL;
	sphere = sphere_stub();
	i1 = intersection(1, sphere);
	i2 = intersection(2, sphere);
	insert_intersection(&xs, i1);
	insert_intersection(&xs, i2);
	i = hit(xs);
	cr_assert(eq(i32, intersection_count(xs), 2));
	cr_assert(eq(i32, compare_spheres(i->object.sphere, sphere), TRUE));
	erase_intersections(&xs);
}

Test(intersections, hit_when_all_intersections_have_negative_t)
{
	t_sphere		sphere;
	t_intersection	*result;
	t_intersection	*expected;
	t_intersection	*xs;

	xs = NULL;
	sphere = sphere_stub();
	result = intersection(-2, sphere);
	insert_intersection(&xs, result);
	result = intersection(-1, sphere);
	insert_intersection(&xs, result);
	expected = hit(xs);
	cr_assert(eq(i32, intersection_count(xs), 2));
	cr_assert(eq(ptr, expected, NULL));
	erase_intersections(&xs);
}

Test(intersections, the_hit_is_always_the_lowest_nonnegative_intersection)
{
	t_sphere		sphere;
	t_intersection	*i1;
	t_intersection	*xs;
	t_intersection	*i;

	xs = NULL;
	sphere = sphere_stub();
	i1 = intersection(5, sphere);
	insert_intersection(&xs, i1);
	i1 = intersection(7, sphere);
	insert_intersection(&xs, i1);
	i1 = intersection(-3, sphere);
	insert_intersection(&xs, i1);
	i1 = intersection(2, sphere);
	insert_intersection(&xs, i1);
	i = hit(xs);
	cr_assert(eq(i32, intersection_count(xs), 4));
	cr_assert(eq(flt, i->t, 2));
	erase_intersections(&xs);
}
