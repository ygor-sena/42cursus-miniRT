/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_patterns.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:37:57 by yde-goes          #+#    #+#             */
/*   Updated: 2023/06/02 16:02:41 by yde-goes         ###   ########.fr       */
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

/* Test(patterns, checkers_should_repeat_in_x_3)
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
} */

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

/* Test(patterns, checkers_should_repeat_in_y_3)
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
} */

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

/* Test(patterns, checkers_should_repeat_in_z_3)
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
} */

Test(patterns, checker_pattern_in_2D_1)
{
	t_checker	checkers;
	t_color		res;
	t_color		expected;

	checkers = uv_checkers(2, 2, BLACK, WHITE);
	res = uv_pattern_at(checkers, 0.0, 0.0);
	expected = BLACK;

	cr_assert(eq(flt, res.red, expected.red));
	cr_assert(eq(flt, res.green, expected.green));
	cr_assert(eq(flt, res.blue, expected.blue));
}

Test(patterns, checker_pattern_in_2D_2)
{
	t_checker	checkers;
	t_color		res;
	t_color		expected;

	checkers = uv_checkers(2, 2, BLACK, WHITE);
	res = uv_pattern_at(checkers, 0.5, 0.0);
	expected = WHITE;

	cr_assert(eq(flt, res.red, expected.red));
	cr_assert(eq(flt, res.green, expected.green));
	cr_assert(eq(flt, res.blue, expected.blue));
}

Test(patterns, checker_pattern_in_2D_3)
{
	t_checker	checkers;
	t_color		res;
	t_color		expected;

	checkers = uv_checkers(2, 2, BLACK, WHITE);
	res = uv_pattern_at(checkers, 0.0, 0.5);
	expected = WHITE;

	cr_assert(eq(flt, res.red, expected.red));
	cr_assert(eq(flt, res.green, expected.green));
	cr_assert(eq(flt, res.blue, expected.blue));
}

Test(patterns, checker_pattern_in_2D_4)
{
	t_checker	checkers;
	t_color		res;
	t_color		expected;

	checkers = uv_checkers(2, 2, BLACK, WHITE);
	res = uv_pattern_at(checkers, 0.5, 0.5);
	expected = BLACK;

	cr_assert(eq(flt, res.red, expected.red));
	cr_assert(eq(flt, res.green, expected.green));
	cr_assert(eq(flt, res.blue, expected.blue));
}

Test(patterns, checker_pattern_in_2D_5)
{
	t_checker	checkers;
	t_color		res;
	t_color		expected;

	checkers = uv_checkers(2.0, 2.0, BLACK, WHITE);
	res = uv_pattern_at(checkers, 1.0, 1.0);
	expected = BLACK;

	cr_assert(eq(flt, res.red, expected.red));
	cr_assert(eq(flt, res.green, expected.green));
	cr_assert(eq(flt, res.blue, expected.blue));
}

/* Using a spherical mapping on a 3D point */
Test(patterns, sphere_mapping_3D_point_1)
{
	t_point		p;
	t_checker	u;
	t_checker	v;
	
	p = point(0, 0, -1);
	u = spherical_map(p);
	v = spherical_map(p);

	cr_assert(eq(flt, u.width, 0.0));
	cr_assert(eq(flt, v.height, 0.5));
}

/* Using a spherical mapping on a 3D point */
Test(patterns, sphere_mapping_3D_point_2)
{
	t_point		p;
	t_checker	u;
	t_checker	v;
	
	p = point(1, 0, 0);
	u = spherical_map(p);
	v = spherical_map(p);

	cr_assert(eq(flt, u.width, 0.25));
	cr_assert(eq(flt, v.height, 0.5));
}

/* Using a spherical mapping on a 3D point */
Test(patterns, sphere_mapping_3D_point_3)
{
	t_point		p;
	t_checker	u;
	t_checker	v;
	
	p = point(0, 0, 1);
	u = spherical_map(p);
	v = spherical_map(p);

	cr_assert(eq(flt, u.width, 0.5));
	cr_assert(eq(flt, v.height, 0.5));
}

/* Using a spherical mapping on a 3D point */
Test(patterns, sphere_mapping_3D_point_4)
{
	t_point		p;
	t_checker	u;
	t_checker	v;
	
	p = point(-1, 0, 0);
	u = spherical_map(p);
	v = spherical_map(p);

	cr_assert(eq(flt, u.width, 0.75));
	cr_assert(eq(flt, v.height, 0.5));
}

/* Using a spherical mapping on a 3D point */
Test(patterns, sphere_mapping_3D_point_5)
{
	t_point		p;
	t_checker	u;
	t_checker	v;
	
	p = point(0, 1, 0);
	u = spherical_map(p);
	v = spherical_map(p);

	cr_assert(eq(flt, u.width, 0.5));
	cr_assert(eq(flt, v.height, 1.0));
}

/* Using a spherical mapping on a 3D point */
Test(patterns, sphere_mapping_3D_point_6)
{
	t_point		p;
	t_checker	u;
	t_checker	v;
	
	p = point(0, -1, 0);
	u = spherical_map(p);
	v = spherical_map(p);

	cr_assert(eq(flt, u.width, 0.5));
	cr_assert(eq(flt, v.height, 0.0));
}

/* Using a spherical mapping on a 3D point */
Test(patterns, sphere_mapping_3D_point_7)
{
	t_point		p;
	t_checker	u;
	t_checker	v;
	
	p = point(sqrt(2)/2.0, sqrt(2)/2.0, 0);
	u = spherical_map(p);
	v = spherical_map(p);

	cr_assert(eq(flt, u.width, 0.25));
	cr_assert(eq(flt, v.height, 0.75));
}

/* Using a texture map pattern with a spherical map */
Test(patterns, texture_map_with_spherical_map_01)
{
	t_checker	checkers;
	t_pattern	pattern;
	t_point		p;
	t_color		res;
	t_color		expected;
	
	checkers = uv_checkers(16, 8, BLACK, WHITE);
	pattern = new_pattern(BLACK, WHITE);
	pattern.pattern_at = checkered_at;
	texture_map(&pattern, checkers, spherical_map);
	p = point(0.4315, 0.4670, 0.7719);
	expected = WHITE;
	
	res = pattern.pattern_at(pattern, p);
	cr_assert(eq(flt, res.red, expected.red));
	cr_assert(eq(flt, res.green, expected.green));
	cr_assert(eq(flt, res.blue, expected.blue));
}

/* Using a texture map pattern with a spherical map */
Test(patterns, texture_map_with_spherical_map_02)
{
	t_checker	checkers;
	t_pattern	pattern;
	t_point		p;
	t_color		res;
	t_color		expected;
	
	checkers = uv_checkers(16, 8, BLACK, WHITE);
	pattern = new_pattern(BLACK, WHITE);
	pattern.pattern_at = checkered_at;
	texture_map(&pattern, checkers, spherical_map);
	p = point(-0.9654, 0.2552, -0.0534);
	expected = BLACK;
	
	res = pattern.pattern_at(pattern, p);
	cr_assert(eq(flt, res.red, expected.red));
	cr_assert(eq(flt, res.green, expected.green));
	cr_assert(eq(flt, res.blue, expected.blue));
}

/* Using a texture map pattern with a spherical map */
Test(patterns, texture_map_with_spherical_map_03)
{
	t_checker	checkers;
	t_pattern	pattern;
	t_point		p;
	t_color		res;
	t_color		expected;
	
	checkers = uv_checkers(16, 8, BLACK, WHITE);
	pattern = new_pattern(BLACK, WHITE);
	pattern.pattern_at = checkered_at;
	texture_map(&pattern, checkers, spherical_map);
	p = point(0.1039, 0.7090, 0.6975);
	expected = WHITE;
	
	res = pattern.pattern_at(pattern, p);
	cr_assert(eq(flt, res.red, expected.red));
	cr_assert(eq(flt, res.green, expected.green));
	cr_assert(eq(flt, res.blue, expected.blue));
}

/* Using a texture map pattern with a spherical map */
Test(patterns, texture_map_with_spherical_map_04)
{
	t_checker	checkers;
	t_pattern	pattern;
	t_point		p;
	t_color		res;
	t_color		expected;
	
	checkers = uv_checkers(16, 8, BLACK, WHITE);
	pattern = new_pattern(BLACK, WHITE);
	pattern.pattern_at = checkered_at;
	texture_map(&pattern, checkers, spherical_map);
	p = point(-0.4986, -0.7856, -0.3663);
	expected = BLACK;
	
	res = pattern.pattern_at(pattern, p);
	cr_assert(eq(flt, res.red, expected.red));
	cr_assert(eq(flt, res.green, expected.green));
	cr_assert(eq(flt, res.blue, expected.blue));
}

/* Using a texture map pattern with a spherical map */
Test(patterns, texture_map_with_spherical_map_05)
{
	t_checker	checkers;
	t_pattern	pattern;
	t_point		p;
	t_color		res;
	t_color		expected;
	
	checkers = uv_checkers(16, 8, BLACK, WHITE);
	pattern = new_pattern(BLACK, WHITE);
	pattern.pattern_at = checkered_at;
	texture_map(&pattern, checkers, spherical_map);
	p = point(-0.0317, -0.9395, 0.3411);
	expected = BLACK;
	
	res = pattern.pattern_at(pattern, p);
	cr_assert(eq(flt, res.red, expected.red));
	cr_assert(eq(flt, res.green, expected.green));
	cr_assert(eq(flt, res.blue, expected.blue));
}

/* Using a texture map pattern with a spherical map */
Test(patterns, texture_map_with_spherical_map_06)
{
	t_checker	checkers;
	t_pattern	pattern;
	t_point		p;
	t_color		res;
	t_color		expected;
	
	checkers = uv_checkers(16, 8, BLACK, WHITE);
	pattern = new_pattern(BLACK, WHITE);
	pattern.pattern_at = checkered_at;
	texture_map(&pattern, checkers, spherical_map);
	p = point(0.4809, -0.7721, 0.4154);
	expected = BLACK;
	
	res = pattern.pattern_at(pattern, p);
	cr_assert(eq(flt, res.red, expected.red));
	cr_assert(eq(flt, res.green, expected.green));
	cr_assert(eq(flt, res.blue, expected.blue));
}

/* Using a texture map pattern with a spherical map */
Test(patterns, texture_map_with_spherical_map_07)
{
	t_checker	checkers;
	t_pattern	pattern;
	t_point		p;
	t_color		res;
	t_color		expected;
	
	checkers = uv_checkers(16, 8, BLACK, WHITE);
	pattern = new_pattern(BLACK, WHITE);
	pattern.pattern_at = checkered_at;
	texture_map(&pattern, checkers, spherical_map);
	p = point(0.0285, -0.9612, -0.2745);
	expected = BLACK;
	
	res = pattern.pattern_at(pattern, p);
	cr_assert(eq(flt, res.red, expected.red));
	cr_assert(eq(flt, res.green, expected.green));
	cr_assert(eq(flt, res.blue, expected.blue));
}

/* Using a texture map pattern with a spherical map */
Test(patterns, texture_map_with_spherical_map_08)
{
	t_checker	checkers;
	t_pattern	pattern;
	t_point		p;
	t_color		res;
	t_color		expected;
	
	checkers = uv_checkers(16, 8, BLACK, WHITE);
	pattern = new_pattern(BLACK, WHITE);
	pattern.pattern_at = checkered_at;
	texture_map(&pattern, checkers, spherical_map);
	p = point(-0.5734, -0.2162, -0.7903);
	expected = WHITE;
	
	res = pattern.pattern_at(pattern, p);
	cr_assert(eq(flt, res.red, expected.red));
	cr_assert(eq(flt, res.green, expected.green));
	cr_assert(eq(flt, res.blue, expected.blue));
}

/* Using a texture map pattern with a spherical map */
Test(patterns, texture_map_with_spherical_map_09)
{
	t_checker	checkers;
	t_pattern	pattern;
	t_point		p;
	t_color		res;
	t_color		expected;
	
	checkers = uv_checkers(16, 8, BLACK, WHITE);
	pattern = new_pattern(BLACK, WHITE);
	pattern.pattern_at = checkered_at;
	texture_map(&pattern, checkers, spherical_map);
	p = point(0.7688, -0.1470, 0.6223);
	expected = BLACK;
	
	res = pattern.pattern_at(pattern, p);
	cr_assert(eq(flt, res.red, expected.red));
	cr_assert(eq(flt, res.green, expected.green));
	cr_assert(eq(flt, res.blue, expected.blue));
}

/* Using a texture map pattern with a spherical map */
Test(patterns, texture_map_with_spherical_map_10)
{
	t_checker	checkers;
	t_pattern	pattern;
	t_point		p;
	t_color		res;
	t_color		expected;
	
	checkers = uv_checkers(16, 8, BLACK, WHITE);
	pattern = new_pattern(BLACK, WHITE);
	pattern.pattern_at = checkered_at;
	texture_map(&pattern, checkers, spherical_map);
	p = point(-0.7652, 0.2175, 0.6060);
	expected = BLACK;
	
	res = pattern.pattern_at(pattern, p);
	cr_assert(eq(flt, res.red, expected.red));
	cr_assert(eq(flt, res.green, expected.green));
	cr_assert(eq(flt, res.blue, expected.blue));
}

/* Using a planar mapping on a 3D point */
Test(patterns, planar_mapping_3D_point_01)
{
	t_point		p;
	t_checker	u;
	t_checker	v;
	
	p = point(0.25, 0, 0.5);
	u = planar_map(p);
	v = planar_map(p);

	cr_assert(eq(flt, u.width, 0.25));
	cr_assert(eq(flt, v.height, 0.5));
}

/* Using a planar mapping on a 3D point */
Test(patterns, planar_mapping_3D_point_02)
{
	t_point		p;
	t_checker	u;
	t_checker	v;
	
	p = point(0.25, 0, -0.25);
	u = planar_map(p);
	v = planar_map(p);

	cr_assert(eq(flt, u.width, 0.25));
	cr_assert(eq(flt, v.height, 0.75));
}

/* Using a planar mapping on a 3D point */
Test(patterns, planar_mapping_3D_point_03)
{
	t_point		p;
	t_checker	u;
	t_checker	v;
	
	p = point(0.25, 0.5, -0.25);
	u = planar_map(p);
	v = planar_map(p);

	cr_assert(eq(flt, u.width, 0.25));
	cr_assert(eq(flt, v.height, 0.75));
}

/* Using a planar mapping on a 3D point */
Test(patterns, planar_mapping_3D_point_04)
{
	t_point		p;
	t_checker	u;
	t_checker	v;
	
	p = point(1.25, 0, 0.5);
	u = planar_map(p);
	v = planar_map(p);

	cr_assert(eq(flt, u.width, 0.25));
	cr_assert(eq(flt, v.height, 0.5));
}

/* Using a planar mapping on a 3D point */
Test(patterns, planar_mapping_3D_point_05)
{
	t_point		p;
	t_checker	u;
	t_checker	v;
	
	p = point(0.25, 0, -1.75);
	u = planar_map(p);
	v = planar_map(p);

	cr_assert(eq(flt, u.width, 0.25));
	cr_assert(eq(flt, v.height, 0.25));
}

/* Using a planar mapping on a 3D point */
Test(patterns, planar_mapping_3D_point_06)
{
	t_point		p;
	t_checker	u;
	t_checker	v;
	
	p = point(1, 0, -1);
	u = planar_map(p);
	v = planar_map(p);

	cr_assert(eq(flt, u.width, 0.0));
	cr_assert(eq(flt, v.height, 0.0));
}

/* Using a planar mapping on a 3D point */
Test(patterns, planar_mapping_3D_point_07)
{
	t_point		p;
	t_checker	u;
	t_checker	v;
	
	p = point(0, 0, 0);
	u = planar_map(p);
	v = planar_map(p);

	cr_assert(eq(flt, u.width, 0.0));
	cr_assert(eq(flt, v.height, 0.0));
}

/* Using a cylindrical mapping on a 3D point */
Test(patterns, cylindrical_mapping_3D_point_01)
{
	t_point		p;
	t_checker	u;
	t_checker	v;
	
	p = point(0, 0, -1);
	u = cylindrical_map(p);
	v = cylindrical_map(p);

	cr_assert(eq(flt, u.width, 0.0));
	cr_assert(eq(flt, v.height, 0.0));
}

/* Using a cylindrical mapping on a 3D point */
Test(patterns, cylindrical_mapping_3D_point_02)
{
	t_point		p;
	t_checker	u;
	t_checker	v;
	
	p = point(0, 0.5, -1);
	u = cylindrical_map(p);
	v = cylindrical_map(p);

	cr_assert(eq(flt, u.width, 0.0));
	cr_assert(eq(flt, v.height, 0.5));
}

/* Using a cylindrical mapping on a 3D point */
Test(patterns, cylindrical_mapping_3D_point_03)
{
	t_point		p;
	t_checker	u;
	t_checker	v;
	
	p = point(0, 1, -1);
	u = cylindrical_map(p);
	v = cylindrical_map(p);

	cr_assert(eq(flt, u.width, 0.0));
	cr_assert(eq(flt, v.height, 0.0));
}

/* Using a cylindrical mapping on a 3D point */
Test(patterns, cylindrical_mapping_3D_point_04)
{
	t_point		p;
	t_checker	u;
	t_checker	v;
	
	p = point(0.70711, 0.5, -0.70711);
	u = cylindrical_map(p);
	v = cylindrical_map(p);

	cr_assert(eq(flt, u.width, 0.125));
	cr_assert(eq(flt, v.height, 0.5));
}

/* Using a cylindrical mapping on a 3D point */
Test(patterns, cylindrical_mapping_3D_point_05)
{
	t_point		p;
	t_checker	u;
	t_checker	v;
	
	p = point(1, 0.5, 0);
	u = cylindrical_map(p);
	v = cylindrical_map(p);

	cr_assert(eq(flt, u.width, 0.25));
	cr_assert(eq(flt, v.height, 0.5));
}

/* Using a cylindrical mapping on a 3D point */
Test(patterns, cylindrical_mapping_3D_point_06)
{
	t_point		p;
	t_checker	u;
	t_checker	v;
	
	p = point(0.70711, 0.5, 0.70711);
	u = cylindrical_map(p);
	v = cylindrical_map(p);

	cr_assert(eq(flt, u.width, 0.375));
	cr_assert(eq(flt, v.height, 0.5));
}

/* Using a cylindrical mapping on a 3D point */
Test(patterns, cylindrical_mapping_3D_point_07)
{
	t_point		p;
	t_checker	u;
	t_checker	v;
	
	p = point(0, -0.25, 1);
	u = cylindrical_map(p);
	v = cylindrical_map(p);

	cr_assert(eq(flt, u.width, 0.5));
	cr_assert(eq(flt, v.height, 0.75));
}

/* Using a cylindrical mapping on a 3D point */
Test(patterns, cylindrical_mapping_3D_point_08)
{
	t_point		p;
	t_checker	u;
	t_checker	v;
	
	p = point(-0.70711, 0.5, 0.70711);
	u = cylindrical_map(p);
	v = cylindrical_map(p);

	cr_assert(eq(flt, u.width, 0.625));
	cr_assert(eq(flt, v.height, 0.5));
}

/* Using a cylindrical mapping on a 3D point */
Test(patterns, cylindrical_mapping_3D_point_09)
{
	t_point		p;
	t_checker	u;
	t_checker	v;
	
	p = point(-1, 1.25, 0);
	u = cylindrical_map(p);
	v = cylindrical_map(p);

	cr_assert(eq(flt, u.width, 0.75));
	cr_assert(eq(flt, v.height, 0.25));
}


/* Using a cylindrical mapping on a 3D point */
Test(patterns, cylindrical_mapping_3D_point_10)
{
	t_point		p;
	t_checker	u;
	t_checker	v;
	
	p = point(-0.70711, 0.5, -0.70711);
	u = cylindrical_map(p);
	v = cylindrical_map(p);

	cr_assert(eq(flt, u.width, 0.875));
	cr_assert(eq(flt, v.height, 0.5));
}
