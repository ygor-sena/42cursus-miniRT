/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:55:26 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/27 14:50:23 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"
#include "utils.h"

/* Should return a empty world, containing no objects and no light source. */
Test(world, creating_a_world)
{
	t_world	w;

	w = world_stub();
	cr_assert(eq(ptr, w.objects, NULL));
	cr_assert(eq(ptr, w.lights, NULL));
}

Test(world, the_default_world)
{
	t_world		w;
	t_shape		s1;
	t_shape		s2;
	t_light		light;
	t_light		w_light;

	light = point_light(point(-10, 10, -10), new_color(1, 1, 1));
	w = default_world();
	w_light = w.lights[0];

	cr_assert(eq(flt, w_light.position.x, light.position.x));
	cr_assert(eq(flt, w_light.position.y, light.position.y));
	cr_assert(eq(flt, w_light.position.z, light.position.z));
	cr_assert(eq(flt, w_light.intensity.red, light.intensity.red));
	cr_assert(eq(flt, w_light.intensity.green, light.intensity.green));
	cr_assert(eq(flt, w_light.intensity.blue, light.intensity.blue));

	s1 = w.objects[0];
	cr_assert(eq(flt, s1.sphere.radius, 0.5));
	s2 = w.objects[1];
	cr_assert(eq(flt, s2.sphere.radius, 1.0));
}

Test(world, intersect_a_world_with_a_ray)
{
	t_world	w;
	t_ray	r;
	t_hit	*xs;
	t_hit	*s;

	xs = NULL;
	w = default_world();
	r = new_ray(point(0, 0, -5), vector(0, 0, 1));
	xs = intersect_world(&w, r);

	cr_assert(eq(i32, intersection_count(xs), 4));
	s = xs;
	cr_assert(eq(flt, s->t, 4));
	s = s->next;
	cr_assert(eq(flt, s->t, 4.5));
	s = s->next;
	cr_assert(eq(flt, s->t, 5.5));
	s = s->next;
	cr_assert(eq(flt, s->t, 6));
}

Test(world, precomputing_intersections)
{
	t_shape	shape;
	t_ray	r;
	t_hit	*i;
	t_comps	comps;

	r = new_ray(point(0, 0, -5), vector(0, 0, 1));
	shape = new_shape();
	i = intersection(4, &shape);
	comps = prepare_computations(i, r);

	cr_assert(eq(flt, comps.t, i->t));
	cr_assert(eq(i32, compare_spheres(&comps.object->sphere, &i->object->sphere), TRUE));
	cr_assert(eq(i32, compare_tuples(comps.point, point(0, 0, -1)), TRUE));
	cr_assert(eq(i32, compare_tuples(comps.sight.eyev, point(0, 0, -1)), TRUE));
	cr_assert(eq(i32, compare_tuples(comps.sight.normalv, point(0, 0, -1)), TRUE));
}

Test(world, intersection_outside)
{
	t_ray	r;
	t_shape	shape;
	t_hit	*i;
	t_comps	comps;

	r = new_ray(point(0, 0, -5), vector(0, 0, 1));
	shape = new_sphere();
	i = intersection(4, &shape);
	comps = prepare_computations(i, r);

	cr_assert(eq(i32, comps.inside, FALSE));
}

Test(world, intersection_inside)
{
	t_ray	r;
	t_shape	shape;
	t_hit	*i;
	t_comps	comps;

	r = new_ray(point(0, 0, 0), vector(0, 0, 1));
	shape = new_sphere();
	i = intersection(1, &shape);
	comps = prepare_computations(i, r);

	cr_assert(eq(i32, compare_tuples(comps.point, point(0, 0, 1)), TRUE));
	cr_assert(eq(i32, compare_tuples(comps.sight.eyev, point(0, 0, -1)), TRUE));
	cr_assert(eq(i32, comps.inside, TRUE));
	cr_assert(eq(i32, compare_tuples(comps.sight.normalv, point(0, 0, -1)), TRUE));
}

Test(world, shading_intersection)
{
	t_world	w;
	t_ray	r;
	t_hit	*i;
	t_comps	comps;
	t_color	c;
	t_color	expected;

	w = default_world();
	i = intersection(4, w.objects);
	r = new_ray(point(0, 0, -5), vector(0, 0, 1));
	comps = prepare_computations(i, r);
	c = shade_hit(w, comps);
	expected = new_color(0.38066, 0.47583, 0.2855);

	cr_assert_float_eq(c.red, expected.red, EPSILON);
	cr_assert_float_eq(c.green, expected.green, EPSILON);
	cr_assert_float_eq(c.blue, expected.blue, EPSILON);
}

Test(world, shading_intersection_from_inside)
{
	t_world	w;
	t_ray	r;
	t_shape	shape;
	t_hit	*i;
	t_comps	comps;
	t_color	c;
	t_color	expected;

	w = default_world();
	w.lights[0] = point_light(point(0,0.25, 0), new_color(1, 1, 1));
	r = new_ray(point(0, 0, 0), vector(0, 0, 1));
	shape = w.objects[1];
	i = intersection(0.5, &shape);
	comps = prepare_computations(i, r);
	c = shade_hit(w, comps);
	expected = new_color(0.90498, 0.90498, 0.90498);

	cr_assert_float_eq(c.red, expected.red, EPSILON);
	cr_assert_float_eq(c.green, expected.green, EPSILON);
	cr_assert_float_eq(c.blue, expected.blue, EPSILON);
}

Test(world, color_for_missed_ray)
{
	t_world	w;
	t_ray	r;
	t_color	c;
	t_color	expected;

	w = default_world();
	r = new_ray(point(0, 0, -5), vector(0, 1, 0));
	c = color_at(w, r);
	expected = new_color(0, 0, 0);

	cr_assert_float_eq(c.red, expected.red, EPSILON);
	cr_assert_float_eq(c.green, expected.green, EPSILON);
	cr_assert_float_eq(c.blue, expected.blue, EPSILON);
}

Test(world, color_when_a_ray_hits)
{
	t_world	w;
	t_ray	r;
	t_color	c;
	t_color	expected;

	w = default_world();
	r = new_ray(point(0, 0, -5), vector(0, 0, 1));
	c = color_at(w, r);
	expected = new_color(0.38066, 0.47583, 0.2855);

	cr_assert_float_eq(c.red, expected.red, EPSILON);
	cr_assert_float_eq(c.green, expected.green, EPSILON);
	cr_assert_float_eq(c.blue, expected.blue, EPSILON);
}

Test(world, color_with_an_intersection_behind_the_ray)
{
	t_world	w;
	t_ray	r;
	t_shape	*outter;
	t_shape	*inner;
	t_color	c;

	w = default_world();
	outter = w.objects;
	outter->material.ambient = 1;
	inner = w.objects + 1;
	inner->material.ambient = 1;
	r = new_ray(point(0, 0, 0.75), vector(0, 0, -1));
	c = color_at(w, r);

	cr_assert_float_eq(c.red, inner->material.color.red, EPSILON);
}
