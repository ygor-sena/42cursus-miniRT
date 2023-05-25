/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:09:12 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/21 16:11:12 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/* Test if a newly created shape has a default transformation
 * matrix set to the identity matrix. */
Test(shapes, the_default_transformation)
{
	t_shape	s;

	s = new_shape();
	assert_matrix_equal(s.transform, get_identity_matrix());
}

/* Test if the transformation matrix of a shape can be successfully changed. */
Test(shapes, assigning_a_transformation)
{
	t_shape		s;
	t_matrix	expected;

	s = new_shape();
	expected = translation(2, 3, 3);
	set_transform(&s, expected);
	assert_matrix_equal(s.transform, expected);
}

/* Test that when a shape is created, it has a default material assigned to it. */
Test(shapes, the_default_material)
{
	t_shape		s;
	t_material	result;
	t_material	expected;

	s = new_shape();
	result = s.material;
	expected = material();

	cr_assert_float_eq(result.color.red, expected.color.red, EPSILON);
	cr_assert_float_eq(result.color.green, expected.color.green, EPSILON);
	cr_assert_float_eq(result.color.blue, expected.color.blue, EPSILON);
	cr_assert_float_eq(result.ambient.red, expected.ambient.red, EPSILON);
	cr_assert_float_eq(result.ambient.green, expected.ambient.green, EPSILON);
	cr_assert_float_eq(result.ambient.blue, expected.ambient.blue, EPSILON);
	cr_assert_float_eq(result.diffuse, expected.diffuse, EPSILON);
	cr_assert_float_eq(result.specular, expected.specular, EPSILON);
	cr_assert_float_eq(result.shininess, expected.shininess, EPSILON);
}

/* Test if a material can be successfully assigned to a shape. */
Test(shapes, assigning_a_material)
{
	t_shape		s;
	t_material	expected;

	s = new_shape();
	expected = material();
	expected.ambient = new_color(1, 1, 1);
	s.material = expected;

	cr_assert_float_eq(s.material.color.red, expected.color.red, EPSILON);
	cr_assert_float_eq(s.material.color.green, expected.color.green, EPSILON);
	cr_assert_float_eq(s.material.color.blue, expected.color.blue, EPSILON);
	cr_assert_float_eq(s.material.ambient.red, expected.ambient.red, EPSILON);
	cr_assert_float_eq(s.material.ambient.green, expected.ambient.green, EPSILON);
	cr_assert_float_eq(s.material.ambient.blue, expected.ambient.blue, EPSILON);
	cr_assert_float_eq(s.material.diffuse, expected.diffuse, EPSILON);
	cr_assert_float_eq(s.material.specular, expected.specular, EPSILON);
	cr_assert_float_eq(s.material.shininess, expected.shininess, EPSILON);
}

/* Tests the ability to compute the normal of a geometric shape that has been
 * translated to a specific position. */
Test(shapes, normal_on_a_translated_shape)
{
	t_shape		s;
	t_vector	n;

	s = new_sphere();
	set_transform(&s, translation(0, 1, 0));
	n = s.normal_at(&s, point(0, 1.70711, -0.70711));

	cr_assert_float_eq(n.x, 0, EPSILON);
	cr_assert_float_eq(n.y, 0.70711, EPSILON);
	cr_assert_float_eq(n.z, -0.70711, EPSILON);
}

/* Tests the ability to compute the normal of a geometric shape that has been
 * transformed through a sequence of transformations. */
Test(shapes, normal_on_a_transformed_shape)
{
	t_shape		s;
	t_matrix	m;
	t_vector	n;

	s = new_sphere();
	m = multiply_mx_mx(scaling(1, 0.5, 1), rotation_z(M_PI/5));
	set_transform(&s, m);
	n = s.normal_at(&s, point(0, sqrtf(2)/2, -sqrtf(2)/2));

	cr_assert_float_eq(n.x, 0, EPSILON);
	cr_assert_float_eq(n.y, 0.97014, EPSILON);
	cr_assert_float_eq(n.z, -0.24254, EPSILON);
}
