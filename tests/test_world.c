/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:55:26 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/12 10:42:06 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/* Should return a empty world, containing no objects and no light source. */
Test(world, creating_a_world)
{
	t_world	w;

	w = world_stub();
	cr_assert(eq(ptr, w.objects, NULL));
	cr_assert(eq(ptr, w.lights, NULL));
}

/* Checks if the default world is correctly configured */
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

/* Test if a list of intersections is correctly returned for a ray passing
 * through the center of two spheres in the default world. */
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

/* Test if the function prepare_computations accurately precomputes the
 * intersection point, eye vector, and normal vector in world space for
 * a given ray-object intersection. */
Test(world, precomputing_intersections)
{
	t_shape	sphere;
	t_ray	r;
	t_hit	*i;
	t_comps	comps;

	r = new_ray(point(0, 0, -5), vector(0, 0, 1));
	sphere = new_sphere();
	i = intersection(4, &sphere);
	comps = prepare_computations(i, r);

	cr_assert(eq(flt, comps.t, i->t));
	cr_assert(eq(i32, compare_spheres(&comps.object->sphere, &i->object->sphere), TRUE));
	cr_assert(eq(i32, compare_tuples(comps.point, point(0, 0, -1)), TRUE));
	cr_assert(eq(i32, compare_tuples(comps.sight.eyev, point(0, 0, -1)), TRUE));
	cr_assert(eq(i32, compare_tuples(comps.sight.normalv, point(0, 0, -1)), TRUE));
}

/* Test if the prepare_computations function correctly determines if an
 * intersection occurs on the inside or outside of an object for a given
 * ray and intersection by checking the "inside" attribute of the
 * returned Computations object. */
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

/* Test if the prepare_computations function accurately precomputes the
 * intersection point, eye vector, and normal vector in world space for
 * a given ray-object intersection on the inside of an object. */
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

/* Test shading an intersection with a ray outside an object and a point light. */
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
	c = shade_hit(w, comps, MAX_RECURSION);
	expected = new_color(0.38066, 0.47583, 0.2855);

	cr_assert_float_eq(c.red, expected.red, EPSILON);
	cr_assert_float_eq(c.green, expected.green, EPSILON);
	cr_assert_float_eq(c.blue, expected.blue, EPSILON);
}

/* Test shading an intersection with a ray inside an object and a point light. */
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
	w.lights[0] = point_light(point(0, 0.25, 0), new_color(1, 1, 1));
	r = new_ray(point(0, 0, 0), vector(0, 0, 1));
	shape = w.objects[1];
	i = intersection(0.5, &shape);
	comps = prepare_computations(i, r);
	c = shade_hit(w, comps, MAX_RECURSION);
	expected = new_color(0.90498, 0.90498, 0.90498);

	cr_assert_float_eq(c.red, expected.red, EPSILON);
	cr_assert_float_eq(c.green, expected.green, EPSILON);
	cr_assert_float_eq(c.blue, expected.blue, EPSILON);
}

/* Checks that when a ray misses all objects in a world, the color returned
 * is black (RGB value of 0, 0, 0). */
Test(world, color_for_missed_ray)
{
	t_world	w;
	t_ray	r;
	t_color	c;
	t_color	expected;

	w = default_world();
	r = new_ray(point(0, 0, -5), vector(0, 1, 0));
	c = color_at(w, r, MAX_RECURSION);
	expected = new_color(0, 0, 0);

	cr_assert_float_eq(c.red, expected.red, EPSILON);
	cr_assert_float_eq(c.green, expected.green, EPSILON);
	cr_assert_float_eq(c.blue, expected.blue, EPSILON);
}

/* Checks that when a ray hits an object in a world, the color returned
 * is the correct color for that object */
Test(world, color_when_a_ray_hits)
{
	t_world	w;
	t_ray	r;
	t_color	c;
	t_color	expected;

	w = default_world();
	r = new_ray(point(0, 0, -5), vector(0, 0, 1));
	c = color_at(w, r, MAX_RECURSION);
	expected = new_color(0.38066, 0.47583, 0.2855);

	cr_assert_float_eq(c.red, expected.red, EPSILON);
	cr_assert_float_eq(c.green, expected.green, EPSILON);
	cr_assert_float_eq(c.blue, expected.blue, EPSILON);
}

/*  Test if the color_at function computes the color correctly when a ray
 *  intersects with an object. It verifies that the inner sphere is
 *  identified as the hit object and its color is returned. */
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
	c = color_at(w, r, MAX_RECURSION);

	cr_assert_float_eq(c.red, inner->material.color.red, EPSILON);
}

/*	There is no shadow when nothing is collinear with point and light */
Test(world, no_shadow_collinear)
{
	t_world	w;
	t_tuple	p;
	t_bool	result;

	w = default_world();
	p = point(0, 10, 0);
	result = is_shadowed(&w, p);

	cr_assert(eq(int, result, FALSE));
}

/*	The shadow when an object is between the point and the light */
Test(world, is_shadow_obj_between_point_and_light)
{
	t_world	w;
	t_tuple	p;
	t_bool	result;

	w = default_world();
	p = point(10, -10, 10);
	result = is_shadowed(&w, p);

	cr_assert(eq(int, result, TRUE));
}

/*	There is no shadow when an object is behind the light */
Test(world, no_shadow_obj_behind_light)
{
	t_world	w;
	t_tuple	p;
	t_bool	result;

	w = default_world();
	p = point(-20, 20, -20);
	result = is_shadowed(&w, p);

	cr_assert(eq(int, result, FALSE));
}

/*	There is no shadow when an object is behind the point */
Test(world, no_shadow_obj_behind_pointcd)
{
	t_world	w;
	t_tuple	p;
	t_bool	result;

	w = default_world();
	p = point(-2, 2, -2);
	result = is_shadowed(&w, p);

	cr_assert(eq(int, result, FALSE));
}

/*	shade_hit() is given an intersection in shadow */
Test(world, shade_hit_intersection_in_shadow)
{
	t_world	w;
	t_shape	s1;
	t_shape	s2;
	t_ray	r;
	t_hit	*i;
	t_comps	comps;
	t_color	c;
	t_color	expected;

	w = default_world();
	w.xs = NULL;
	w.lights = ft_calloc(sizeof(t_light), 2);
	w.objects = ft_calloc(sizeof(t_shape), 3);
	w.object_count = 2;
	w.lights[0] = point_light(point(0, 0, -10), new_color(1, 1, 1));
	s1 = new_sphere();
	s2 = new_sphere();
	s2.transform = translation(0, 0, 10);
	w.objects[0] = s1;
	w.objects[1] = s2;
	r = new_ray(point(0, 0, 5), vector(0, 0, 1));
	i = intersection(4, &s2);
	comps = prepare_computations(i, r);
	c = shade_hit(w, comps, MAX_RECURSION);
	expected = new_color(0.1, 0.1, 0.1);

	cr_assert_float_eq(c.red, expected.red, EPSILON);
	cr_assert_float_eq(c.green, expected.green, EPSILON);
	cr_assert_float_eq(c.blue, expected.blue, EPSILON);
}

/*
 * The reflected color for a nonreflective material. Shows that when a ray
 * strikes a nonreflective surface, the reflected_color() function returns
 * the color black.
 */
Test(world, reflected_color_for_nonreflect_material)
{
	t_world	w;
	t_ray	r;
	t_shape	shape;
	t_hit	*i;
	t_comps	comps;
	t_color	color;
	t_color	expected;

	expected = new_color(0, 0, 0);
	w = default_world();
	r = new_ray(point(0, 0, 0), vector(0, 0, 1));
	shape = w.objects[1];
	shape.material.ambient = 1.0;
	i = intersection(1, &shape);
	comps = prepare_computations(i, r);
	color = reflected_color(w, comps, MAX_RECURSION);

	cr_assert_float_eq(color.red, expected.red, EPSILON);
	cr_assert_float_eq(color.green, expected.green, EPSILON);
	cr_assert_float_eq(color.blue, expected.blue, EPSILON);
}

/*
 * The reflected color for a reflective material. Shows that reflected_color()
 * returns the color via reflection when the struck surface is reflective.
 */
//WARNING: modified test conditions
Test(world, reflected_color_for_reflective_material)
{
	t_world	w;
	t_ray	r;
	t_shape	shape;
	t_hit	*i;
	t_comps	comps;
	t_color	color;
	float	coord;
	t_color	expected;

	expected = new_color(0.19033, 0.23791, 0.14274);
	coord = sqrtf(2)/2.0;
	w = default_world();
	shape = new_plane();
	shape.material.reflective = 0.5;
	shape.transform = translation(0, -1, 0);
	add_shape_to_world(&w, shape);
	r = new_ray(point(0, 0, -3), vector(0, -coord, coord));
	i = intersection(sqrtf(2), &shape);
	comps = prepare_computations(i, r);
	color = reflected_color(w, comps, MAX_RECURSION);

	cr_assert_float_eq(color.red, expected.red, EPSILON);
	cr_assert_float_eq(color.green, expected.green, EPSILON);
	cr_assert_float_eq(color.blue, expected.blue, EPSILON);
}

/*
 * shade_hit() with reflective material. Shows that shade_hit() incorporates
 * the reflected color into the final color.
 */
//WARNING: modified test conditions
Test(world, shade_hit_with_reflective_material)
{
	t_world	w;
	t_ray	r;
	t_shape	shape;
	t_hit	*i;
	t_comps	comps;
	t_color	color;
	float	coord;
	t_color	expected;

	expected = new_color(0.87676, 0.92435, 0.82918);
	coord = sqrtf(2)/2.0;
	w = default_world();
	shape = new_plane();
	shape.material.reflective = 0.5;
	shape.transform = translation(0, -1, 0);
	add_shape_to_world(&w, shape);
	r = new_ray(point(0, 0, -3), vector(0, -coord, coord));
	i = intersection(sqrtf(2), &shape);
	comps = prepare_computations(i, r);
	color = shade_hit(w, comps, MAX_RECURSION);

	cr_assert_float_eq(color.red, expected.red, EPSILON);
	cr_assert_float_eq(color.green, expected.green, EPSILON);
	cr_assert_float_eq(color.blue, expected.blue, EPSILON);
}

/*
 * color_at() with mutually reflective surfaces. shade_hit() calls
 * reflected_vector() which calls color_at(). This test shows that the code
 * safety handles infinite recursion caused by two objects that mutually
 * reflect rays between themselves.
 */
Test(world, color_at_mutual_surface_reflection)
{
	t_world	w;
	t_shape	lower;
	t_shape	upper;
	t_ray	r;
	t_color	color;

	w = default_world();
	w.lights[0] = point_light(point(0, 0, 0), new_color(1, 1, 1));
	lower = new_plane();
	lower.material.reflective = 1.0;
	lower.transform = translation(0, -1, 0);
	add_shape_to_world(&w, lower);
	upper = new_plane();
	upper.material.reflective = 1.0;
	upper.transform = translation(0, 1, 0);
	add_shape_to_world(&w, upper);
	r = new_ray(point(0, 0, 0), vector(0, 1, 0));
	color = color_at(w, r, 0);

	cr_assert(color.red);
	cr_assert(color.green);
	cr_assert(color.blue);
}

/*
 * The reflected color at the maximum recursive depth. This test shows that
 * reflected_color() returns without effect when invoked at the limit of its
 * recursive threshold.
 */
Test(world, reflected_color_max_recursive_depth)
{
	t_world	w;
	t_shape	shape;
	t_ray	r;
	t_hit	*i;
	t_comps	comps;
	t_color	color;
	t_color	expected;
	float	coord;

	expected = new_color(0, 0, 0);
	coord = sqrtf(2)/2.0;
	w = default_world();
	shape = new_plane();
	shape.material.reflective = 0.5;
	shape.transform = translation(0, -1, 0);
	add_shape_to_world(&w, shape);
	r = new_ray(point(0, 0, -3), vector(0, -coord, coord));
	i = intersection(sqrtf(2), &shape);
	comps = prepare_computations(i, r);
	color = reflected_color(w, comps, 0);

	cr_assert_float_eq(color.red, expected.red, EPSILON);
	cr_assert_float_eq(color.green, expected.green, EPSILON);
	cr_assert_float_eq(color.blue, expected.blue, EPSILON);
}
