/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_intersections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 09:28:46 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/25 14:48:10 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "shapes.h"
#include "utils.h"

Test(intersections, an_intersection_encapsulates_t_and_object)
{
	t_sphere		*sphere;
	t_intersection	*i;

	sphere = sphere_stub();
	i = intersection(3.5, sphere);
	cr_assert(eq(flt, i->t, 3.5));
	cr_assert(eq(flt, i->object.sphere->radius, sphere->radius));
	free(sphere);
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
}

Test(intersections, hit_when_all_intersections_have_positive_t)
{
	t_sphere		*sphere;
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
	free(sphere);
}

Test(intersections, hit_when_all_intersections_have_negative_t)
{
	t_sphere		*sphere;
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
	free(sphere);
}

Test(intersections, the_hit_is_always_the_lowest_nonnegative_intersection)
{
	t_sphere		*sphere;
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
	free(sphere);
}

/*	The hit should offset the point */
/* Test(intersections, hit_should_offset_point)
{
	t_ray			r;
	t_sphere		*shape;
	t_intersection	*i;
	t_comps			comps;

	r = new_ray(point(0, 0, -5), vector(0, 0, 1));
	shape = sphere_stub();
	shape->transform = translation(0, 0, 1);
	i = intersection(5, shape);
	comps = prepare_computations(i, r);

	//comps.over_point.z < -EPSILON/2
	cr_assert(lt(flt, comps.over_point.z, -EPSILON/2));
	//comps.point.z > comps.over_point.z
	cr_assert(gt(flt, comps.point.z, comps.over_point.z));
}
 */