/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_patterns.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:37:57 by yde-goes          #+#    #+#             */
/*   Updated: 2023/05/26 09:09:27 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/* Creating a stripe pattern */
Test(patterns, create_stripe_feature)
{
	t_pattern	pattern;
	t_color		white;
	t_color		black;
	
	pattern.a = WHITE;
	pattern.b = BLACK;
	white = new_color(1, 1, 1);
	black = new_color(0, 0, 0);

	cr_assert(eq(flt, pattern.a.red, white.red));
	cr_assert(eq(flt, pattern.a.green, white.green));
	cr_assert(eq(flt, pattern.a.blue, white.blue));

	cr_assert(eq(flt, pattern.b.red, black.red));
	cr_assert(eq(flt, pattern.b.green, black.green));
	cr_assert(eq(flt, pattern.b.blue, black.blue));
}

/* A stripe pattern is constant in y */
Test(patterns, new_pattern_constant_in_y_1)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = point(0, 0, 0);
	pattern = new_pattern(WHITE, BLACK);
	res = pattern.pattern_at(pattern, p);
	expected = WHITE;
	
	cr_assert(eq(flt, res.red, expected.red));
	cr_assert(eq(flt, res.green, expected.green));
	cr_assert(eq(flt, res.blue, expected.blue));
}

Test(patterns, new_pattern_constant_in_y_2)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = point(0, 1, 0);
	pattern = new_pattern(WHITE, BLACK);
	res = pattern.pattern_at(pattern, p);
	expected = WHITE;
	
	cr_assert(eq(flt, res.red, expected.red));
	cr_assert(eq(flt, res.green, expected.green));
	cr_assert(eq(flt, res.blue, expected.blue));
}

Test(patterns, new_pattern_constant_in_y_3)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = point(0, 2, 0);
	pattern = new_pattern(WHITE, BLACK);
	res = pattern.pattern_at(pattern, p);
	expected = WHITE;
	
	cr_assert(eq(flt, res.red, expected.red));
	cr_assert(eq(flt, res.green, expected.green));
	cr_assert(eq(flt, res.blue, expected.blue));
}

/* A stripe pattern is constant in z */
Test(patterns, new_pattern_constant_in_z_1)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = point(0, 0, 0);
	pattern = new_pattern(WHITE, BLACK);
	res = pattern.pattern_at(pattern, p);
	expected = WHITE;
	
	cr_assert(eq(flt, res.red, expected.red));
	cr_assert(eq(flt, res.green, expected.green));
	cr_assert(eq(flt, res.blue, expected.blue));
}

Test(patterns, new_pattern_constant_in_z_2)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = point(0, 0, 1);
	pattern = new_pattern(WHITE, BLACK);
	res = pattern.pattern_at(pattern, p);
	expected = WHITE;
	
	cr_assert(eq(flt, res.red, expected.red));
	cr_assert(eq(flt, res.green, expected.green));
	cr_assert(eq(flt, res.blue, expected.blue));
}

Test(patterns, new_pattern_constant_in_z_3)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = point(0, 0, 2);
	pattern = new_pattern(WHITE, BLACK);
	res = pattern.pattern_at(pattern, p);
	expected = WHITE;
	
	cr_assert(eq(flt, res.red, expected.red));
	cr_assert(eq(flt, res.green, expected.green));
	cr_assert(eq(flt, res.blue, expected.blue));
}

/* A stripe pattern is constant in x */
Test(patterns, new_pattern_constant_in_x_1)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = point(0, 0, 0);
	pattern = new_pattern(WHITE, BLACK);
	res = pattern.pattern_at(pattern, p);
	expected = WHITE;
	
	cr_assert(eq(flt, res.red, expected.red));
	cr_assert(eq(flt, res.green, expected.green));
	cr_assert(eq(flt, res.blue, expected.blue));
}

Test(patterns, new_pattern_constant_in_x_2)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = point(0.9, 0, 0);
	pattern = new_pattern(WHITE, BLACK);
	res = pattern.pattern_at(pattern, p);
	expected = WHITE;
	
	cr_assert(eq(flt, res.red, expected.red));
	cr_assert(eq(flt, res.green, expected.green));
	cr_assert(eq(flt, res.blue, expected.blue));
}

Test(patterns, new_pattern_constant_in_x_3)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = point(1, 0, 0);
	pattern = new_pattern(WHITE, BLACK);
	res = pattern.pattern_at(pattern, p);
	expected = BLACK;
	
	cr_assert(eq(flt, res.red, expected.red));
	cr_assert(eq(flt, res.green, expected.green));
	cr_assert(eq(flt, res.blue, expected.blue));
}

Test(patterns, new_pattern_constant_in_x_4)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = point(-0.1, 0, 0);
	pattern = new_pattern(WHITE, BLACK);
	res = pattern.pattern_at(pattern, p);
	expected = BLACK;
	
	cr_assert(eq(flt, res.red, expected.red));
	cr_assert(eq(flt, res.green, expected.green));
	cr_assert(eq(flt, res.blue, expected.blue));
}

Test(patterns, new_pattern_constant_in_x_5)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = point(-1, 0, 0);
	pattern = new_pattern(WHITE, BLACK);
	res = pattern.pattern_at(pattern, p);
	expected = BLACK;
	
	cr_assert(eq(flt, res.red, expected.red));
	cr_assert(eq(flt, res.green, expected.green));
	cr_assert(eq(flt, res.blue, expected.blue));
}

Test(patterns, new_pattern_constant_in_x_6)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = point(-1.1, 0, 0);
	pattern = new_pattern(WHITE, BLACK);
	res = pattern.pattern_at(pattern, p);
	expected = WHITE;
	
	cr_assert(eq(flt, res.red, expected.red));
	cr_assert(eq(flt, res.green, expected.green));
	cr_assert(eq(flt, res.blue, expected.blue));
}

Test(patterns, lighting_with_stripe_pattern_applied)
{
	t_material	m;
	t_sight		sight;
	t_light		light;
	t_color		c1;
	t_color		c2;
	t_shape		shape;

	shape = new_sphere();
	m = material();
	m.pattern = new_pattern(new_color(1, 1, 1), new_color(0, 0, 0));
	m.ambient = new_color(1, 1, 1);
	m.diffuse = 0;
	m.specular = 0;
	shape.material = m;
	sight.eyev = vector(0, 0, -1);
	sight.normalv = vector(0, 0, -1);
	light = point_light(point(0, 0, -10), new_color(1, 1, 1));
	light.in_shadow = FALSE;
	c1 = lighting(&shape, light, point(0.9, 0, 0), sight);
	//c1 = lighting(m, light, point(0.9, 0, 0), sight);
	c2 = lighting(&shape, light, point(1.1, 0, 0), sight);
	//c2 = lighting(m, light, point(1.1, 0, 0), sight);
	
	cr_assert(eq(flt, c1.red, 1));
	cr_assert(eq(flt, c1.green, 1));
	cr_assert(eq(flt, c1.blue, 1));

	cr_assert(eq(flt, c2.red, 0));
	cr_assert(eq(flt, c2.green, 0));
	cr_assert(eq(flt, c2.blue, 0));
}

/* Stripes with an object transformation */
Test(patterns, stripes_with_object_transformation)
{
	t_shape		object;
	t_pattern	pattern;
	t_color		res;
	t_color		expected;

	object = new_sphere();
	set_transform(&object, scaling(2, 2, 2));
	pattern = new_pattern(WHITE, BLACK);
	res = pattern_at_shape(pattern, &object, point(1.5, 0, 0));
	expected = WHITE;

	cr_assert(eq(flt, res.red, expected.red));
	cr_assert(eq(flt, res.green, expected.green));
	cr_assert(eq(flt, res.blue, expected.blue));
}

/* Stripes with a pattern transformation */
Test(patterns, stripes_with_pattern_transformation)
{
	t_shape		object;
	t_pattern	pattern;
	t_color		res;
	t_color		expected;

	object = new_sphere();
	pattern = new_pattern(WHITE, BLACK);
	set_pattern_transform(&pattern, scaling(2, 2, 2));
	res = pattern_at_shape(pattern, &object, point(1.5, 0, 0));
	expected = WHITE;

	cr_assert(eq(flt, res.red, expected.red));
	cr_assert(eq(flt, res.green, expected.green));
	cr_assert(eq(flt, res.blue, expected.blue));
}

/* Stripes with both an object and a pattern transformation */
Test(patterns, stripes_with_object_and_pattern_transformation)
{
	t_shape		object;
	t_pattern	pattern;
	t_color		res;
	t_color		expected;

	object = new_sphere();
	set_transform(&object, scaling(2, 2, 2));
	pattern = new_pattern(WHITE, BLACK);
	set_pattern_transform(&pattern, translation(0.5, 0, 0));
	res = pattern_at_shape(pattern, &object, point(2.5, 0, 0));
	expected = WHITE;

	cr_assert(eq(flt, res.red, expected.red));
	cr_assert(eq(flt, res.green, expected.green));
	cr_assert(eq(flt, res.blue, expected.blue));
}

/* Checkers should repeat in x */
Test(patterns, checkers_should_repeat_in_x_1)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = point(0, 0, 0);
	pattern = new_pattern(WHITE, BLACK);
	pattern.pattern_at = checkered_at;
	res = pattern.pattern_at(pattern, p);
	expected = WHITE;
	
	cr_assert(eq(flt, res.red, expected.red));
	cr_assert(eq(flt, res.green, expected.green));
	cr_assert(eq(flt, res.blue, expected.blue));
}

Test(patterns, checkers_should_repeat_in_x_2)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = point(0.99, 0, 0);
	pattern = new_pattern(WHITE, BLACK);
	pattern.pattern_at = checkered_at;
	res = pattern.pattern_at(pattern, p);
	expected = WHITE;
	
	cr_assert(eq(flt, res.red, expected.red));
	cr_assert(eq(flt, res.green, expected.green));
	cr_assert(eq(flt, res.blue, expected.blue));
}

Test(patterns, checkers_should_repeat_in_x_3)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = point(1.01, 0, 0);
	pattern = new_pattern(WHITE, BLACK);
	pattern.pattern_at = checkered_at;
	res = pattern.pattern_at(pattern, p);
	expected = BLACK;
	
	cr_assert(eq(flt, res.red, expected.red));
	cr_assert(eq(flt, res.green, expected.green));
	cr_assert(eq(flt, res.blue, expected.blue));
}

/* Checkers should repeat in y */
Test(patterns, checkers_should_repeat_in_y_1)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = point(0, 0, 0);
	pattern = new_pattern(WHITE, BLACK);
	pattern.pattern_at = checkered_at;
	res = pattern.pattern_at(pattern, p);
	expected = WHITE;
	
	cr_assert(eq(flt, res.red, expected.red));
	cr_assert(eq(flt, res.green, expected.green));
	cr_assert(eq(flt, res.blue, expected.blue));
}

Test(patterns, checkers_should_repeat_in_y_2)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = point(0, 0.99, 0);
	pattern = new_pattern(WHITE, BLACK);
	pattern.pattern_at = checkered_at;
	res = pattern.pattern_at(pattern, p);
	expected = WHITE;
	
	cr_assert(eq(flt, res.red, expected.red));
	cr_assert(eq(flt, res.green, expected.green));
	cr_assert(eq(flt, res.blue, expected.blue));
}

Test(patterns, checkers_should_repeat_in_y_3)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = point(0, 1.01, 0);
	pattern = new_pattern(WHITE, BLACK);
	pattern.pattern_at = checkered_at;
	res = pattern.pattern_at(pattern, p);
	expected = BLACK;
	
	cr_assert(eq(flt, res.red, expected.red));
	cr_assert(eq(flt, res.green, expected.green));
	cr_assert(eq(flt, res.blue, expected.blue));
}

/* Checkers should repeat in z */
Test(patterns, checkers_should_repeat_in_z_1)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = point(0, 0, 0);
	pattern = new_pattern(WHITE, BLACK);
	pattern.pattern_at = checkered_at;
	res = pattern.pattern_at(pattern, p);
	expected = WHITE;
	
	cr_assert(eq(flt, res.red, expected.red));
	cr_assert(eq(flt, res.green, expected.green));
	cr_assert(eq(flt, res.blue, expected.blue));
}

Test(patterns, checkers_should_repeat_in_z_2)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = point(0, 0, 0.99);
	pattern = new_pattern(WHITE, BLACK);
	pattern.pattern_at = checkered_at;
	res = pattern.pattern_at(pattern, p);
	expected = WHITE;
	
	cr_assert(eq(flt, res.red, expected.red));
	cr_assert(eq(flt, res.green, expected.green));
	cr_assert(eq(flt, res.blue, expected.blue));
}

Test(patterns, checkers_should_repeat_in_z_3)
{
	t_pattern	pattern;
	t_color		res;
	t_tuple		p;
	t_color		expected;

	p = point(0, 0, 1.01);
	pattern = new_pattern(WHITE, BLACK);
	pattern.pattern_at = checkered_at;
	res = pattern.pattern_at(pattern, p);
	expected = BLACK;
	
	cr_assert(eq(flt, res.red, expected.red));
	cr_assert(eq(flt, res.green, expected.green));
	cr_assert(eq(flt, res.blue, expected.blue));
}
