/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_materials.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 10:46:43 by yde-goes          #+#    #+#             */
/*   Updated: 2023/05/26 09:09:23 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/**
 * ABOUT THIS MODULE TEST_MATERIALS.C
 *
 * A material has a surface color and for attributes
 * from the Phong reflection module: ambient, diffuse, specular and shininess.
 * Each one of these attributes accept a nonnegative floating point number.
 * For ambient, diffuse and specular, the typical values are between 0 and 1.
 * For shininess, values between 10 (very large highlight) and 200 (very small)
 * highlight seem to work best, though there is no actual upper bound.
 */

/* Checks if a default material is created as expected */
Test(materials, create_a_default_material)
{
	t_material	m;
	t_color		color;

	m = material();
	color = new_color(1, 1, 1);

	cr_assert(eq(flt, m.color.red, color.red));
	cr_assert(eq(flt, m.color.green, color.green));
	cr_assert(eq(flt, m.color.blue, color.blue));
	cr_assert(eq(flt, m.ambient.red, 0.1));
	cr_assert(eq(flt, m.ambient.green, 0.1));
	cr_assert(eq(flt, m.ambient.blue, 0.1));
	cr_assert(eq(flt, m.diffuse, 0.9));
	cr_assert(eq(flt, m.specular, 0.9));
	cr_assert(eq(flt, m.shininess, 200.0));
}

/**
 * The following five test will share the same m and position to
 * move the "eye" and the light source around to checks for
 * different cases of the lighting() function.
 */

/* Lighting with the eye between the light and the surface */
Test(materials, eye_between_lt_surface)
{
	t_sight		sight;
	t_light		light;
	t_color		result;
	t_color		expected;

	t_material	m;
	t_tuple		position;
	t_shape		shape;

	m = material();
	shape.material = m;
	position = point(0, 0, 0);

	sight.eyev = vector(0, 0, -1);
	sight.normalv = vector(0, 0, -1);
	light = point_light(point(0, 0, -10), new_color(1, 1, 1));
	result = lighting(&shape, light, position, sight);
	//result = lighting(m, light, position, sight);
	expected = new_color(1.9, 1.9, 1.9);

	cr_assert_float_eq(result.red, expected.red, EPSILON);
	cr_assert_float_eq(result.green, expected.green, EPSILON);
	cr_assert_float_eq(result.blue, expected.blue, EPSILON);
}

/* Lighting with the eye between light and surface, eye offset 45º */
Test(materials, eye_between_lt_surface_offset_45)
{
	t_sight		sight;
	t_light		light;
	t_color		result;
	t_color		expected;
	float		coord;

	t_material	m;
	t_tuple		position;
	t_shape		shape;

	m = material();
	position = point(0, 0, 0);
	shape.material = m;
	
	coord = sqrtf(2)/2.0;
	sight.eyev = vector(0, coord, -coord);
	sight.normalv = vector(0, 0, -1);
	light = point_light(point(0, 0, -10), new_color(1, 1, 1));
	result = lighting(&shape, light, position, sight);
	//result = lighting(m, light, position, sight);
	expected = new_color(1.0, 1.0, 1.0);

	cr_assert_float_eq(result.red, expected.red, EPSILON);
	cr_assert_float_eq(result.green, expected.green, EPSILON);
	cr_assert_float_eq(result.blue, expected.blue, EPSILON);
}

/* Lighting with eye opposite surface, light offset 45° */
Test(materials, eye_opposite_surface_lt_offset_45)
{
	t_sight		sight;
	t_light		light;
	t_color		result;
	t_color		expected;

	t_material	m;
	t_tuple		position;
	t_shape		shape;

	m = material();
	position = point(0, 0, 0);
	shape.material = m;

	sight.eyev = vector(0, 0, -1);
	sight.normalv = vector(0, 0, -1);
	light = point_light(point(0, 10, -10), new_color(1, 1, 1));
	result = lighting(&shape, light, position, sight);
	//result = lighting(m, light, position, sight);
	expected = new_color(0.7364, 0.7364, 0.7364);

	cr_assert_float_eq(result.red, expected.red, EPSILON);
	cr_assert_float_eq(result.green, expected.green, EPSILON);
	cr_assert_float_eq(result.blue, expected.blue, EPSILON);
}

/* Lighting with eye in the path of the reflection vector */
Test(materials, eye_reflection_light_path)
{
	t_sight		sight;
	t_light		light;
	t_color		result;
	t_color		expected;
	float		coord;

	t_material	m;
	t_tuple		position;
	t_shape		shape;

	m = material();
	position = point(0, 0, 0);
	shape.material = m;

	coord = sqrtf(2)/2.0;
	sight.eyev = vector(0, -coord, -coord);
	sight.normalv = vector(0, 0, -1);
	light = point_light(point(0, 10, -10), new_color(1, 1, 1));
	result = lighting(&shape, light, position, sight);
	//result = lighting(m, light, position, sight);
	expected = new_color(1.63639, 1.63639, 1.63639);

	cr_assert_float_eq(result.red, expected.red, EPSILON);
	cr_assert_float_eq(result.green, expected.green, EPSILON);
	cr_assert_float_eq(result.blue, expected.blue, EPSILON);
}

/* Lighting with the light behind the surface */
Test(materials, eye_light_behind_surface)
{
	t_sight		sight;
	t_light		light;
	t_color		result;
	t_color		expected;

	t_material	m;
	t_tuple		position;
	t_shape		shape;

	m = material();
	position = point(0, 0, 0);
	shape.material = m;

	sight.eyev = vector(0, 0, -1);
	sight.normalv = vector(0, 0, -1);
	light = point_light(point(0, 0, 10), new_color(1, 1, 1));
	result = lighting(&shape, light, position, sight);
	//result = lighting(m, light, position, sight);
	expected = new_color(0.1, 0.1, 0.1);

	cr_assert_float_eq(result.red, expected.red, EPSILON);
	cr_assert_float_eq(result.green, expected.green, EPSILON);
	cr_assert_float_eq(result.blue, expected.blue, EPSILON);
}

/* Lighting with the surface in shadow */
Test(materials, lighting_surface_in_shadow)
{
	t_sight		eye;
	t_light		light;
	t_color		result;
	t_color		expected;

	t_material	m;
	t_tuple		position;
	t_shape		shape;

	m = material();
	position = point(0, 0, 0);
	shape.material = m;

	expected = new_color(0.1, 0.1, 0.1);
	eye.eyev = vector(0, 0, 1);
	eye.normalv = vector(0, 0, -1);
	position = point(0, 0, 0);
	light = point_light(point(0, 0, -10), new_color(1, 1, 1));
	light.in_shadow = TRUE;
	result = lighting(&shape, light, position, eye);
	//result = lighting(m, light, position, eye);

	cr_assert_float_eq(result.red, expected.red, EPSILON);
	cr_assert_float_eq(result.green, expected.green, EPSILON);
	cr_assert_float_eq(result.blue, expected.blue, EPSILON);
}
