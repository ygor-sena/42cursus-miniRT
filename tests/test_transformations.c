/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_transformations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 10:59:12 by yde-goes          #+#    #+#             */
/*   Updated: 2023/05/25 14:26:24 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/* Multiplying by a translation matrix */
Test(transformations, mult_by_translation_matrix)
{
	t_matrix	transform;
	t_tuple		p;
	t_tuple		result;

	transform = translation(5.0, -3.0, 2.0);
	p = point(-3.0, 4.0, 5.0);

	result = multiply_tp_mx(transform, p);
	cr_assert(eq(flt, result.x, 2));
	cr_assert(eq(flt, result.y, 1));
	cr_assert(eq(flt, result.z, 7));
}

/* Multiplying by the inverse of a translation matrix */
Test(transformations, mult_by_inv_of_transl_matrix)
{
	t_matrix	transform;
	t_matrix	inv;
	t_tuple		p;
	t_tuple		result;

	transform = translation(5.0, -3.0, 2.0);
	inv = inverse(transform);
	p = point(-3.0, 4.0, 5.0);

	result = multiply_tp_mx(inv, p);
	cr_assert(eq(flt, result.x, -8));
	cr_assert(eq(flt, result.y, 7));
	cr_assert(eq(flt, result.z, 3));
}

/* Translation does not affect vectors */
Test(transformations, transl_doesnt_affect_vectors)
{
	t_matrix	transform;
	t_tuple		v;
	t_tuple		result;

	transform = translation(5.0, -3.0, 2.0);
	v = vector(-3.0, 4.0, 5.0);

	result = multiply_tp_mx(transform, v);
	cr_assert(eq(flt, result.x, v.x));
	cr_assert(eq(flt, result.y, v.y));
	cr_assert(eq(flt, result.z, v.z));
}

/* A scaling matrix applied to a point */
Test(transformations, scaling_matrix_to_point)
{
	t_matrix	transform;
	t_tuple		p;
	t_tuple		result;

	transform = scaling(2.0, 3.0, 4.0);
	p = point(-4.0, 6.0, 8.0);

	result = multiply_tp_mx(transform, p);
	cr_assert(eq(flt, result.x, -8));
	cr_assert(eq(flt, result.y, 18));
	cr_assert(eq(flt, result.z, 32));
}

/* A scaling matrix applied to a vector */
Test(transformations, scaling_matrix_to_vector)
{
	t_matrix	transform;
	t_tuple		v;
	t_tuple		result;

	transform = scaling(2.0, 3.0, 4.0);
	v = vector(-4.0, 6.0, 8.0);

	result = multiply_tp_mx(transform, v);
	cr_assert(eq(flt, result.x, -8));
	cr_assert(eq(flt, result.y, 18));
	cr_assert(eq(flt, result.z, 32));
}

/* Multiplying by the inverse of a scaling matrix */
Test(transformations, mult_by_inv_of_scaling_mat)
{
	t_matrix	transform;
	t_matrix	inv;
	t_tuple		v;
	t_tuple		result;

	transform = scaling(2.0, 3.0, 4.0);
	inv = inverse(transform);
	v = vector(-4.0, 6.0, 8.0);

	result = multiply_tp_mx(inv, v);
	cr_assert(eq(flt, result.x, -2));
	cr_assert(eq(flt, result.y, 2));
	cr_assert(eq(flt, result.z, 2));
}

/* Reflection is scaling by a negative value */
Test(transformations, scaling_by_neg_value)
{
	t_matrix	transform;
	t_tuple		p;
	t_tuple		result;

	transform = scaling(-1.0, 1.0, 1.0);
	p = point(2.0, 3.0, 4.0);

	result = multiply_tp_mx(transform, p);
	cr_assert(eq(flt, result.x, -2));
	cr_assert(eq(flt, result.y, 3));
	cr_assert(eq(flt, result.z, 4));
}

/* Rotating a point around the x axis */
Test(transformations, rotation_around_x_axis)
{
	t_matrix	half_quarter;
	t_matrix	full_quarter;
	t_tuple		p;
	t_tuple		result;

	p = point(0.0, 1.0, 0.0);
	half_quarter = rotation_x(M_PI_4);
	full_quarter = rotation_x(M_PI_2);

	result = multiply_tp_mx(half_quarter, p);
	cr_assert_float_eq(result.x, 0, EPSILON);
	cr_assert_float_eq(result.y, sqrt(2)/2, EPSILON);
	cr_assert_float_eq(result.z, sqrt(2)/2, EPSILON);

	result = multiply_tp_mx(full_quarter, p);
	cr_assert_float_eq(result.x, 0, EPSILON);
	cr_assert_float_eq(result.y, 0, EPSILON);
	cr_assert_float_eq(result.z, 1, EPSILON);
}

/* The inverse of an x-rotation rotates in the opposite direction */
Test(transformations, inv_x_rotation)
{
	t_matrix	half_quarter;
	t_matrix	inv;
	t_tuple		p;
	t_tuple		result;	

	p = point(0.0, 1.0, 0.0);
	half_quarter = rotation_x(M_PI_4);
	inv = inverse(half_quarter);

	result = multiply_tp_mx(inv, p);
	cr_assert_float_eq(result.x, 0, EPSILON);
	cr_assert_float_eq(result.y, sqrt(2)/2, EPSILON);
	cr_assert_float_eq(result.z, -sqrt(2)/2, EPSILON);
}

/* Rotating a point around the y axis */
Test(transformations, rotation_around_y_axis)
{
	t_matrix	half_quarter;
	t_matrix	full_quarter;
	t_tuple		p;
	t_tuple		result;

	p = point(0.0, 0.0, 1.0);
	half_quarter = rotation_y(M_PI_4);
	full_quarter = rotation_y(M_PI_2);

	result = multiply_tp_mx(half_quarter, p);
	cr_assert_float_eq(result.x, sqrt(2)/2, EPSILON);
	cr_assert_float_eq(result.y, 0, EPSILON);
	cr_assert_float_eq(result.z, sqrt(2)/2, EPSILON);

	result = multiply_tp_mx(full_quarter, p);
	cr_assert_float_eq(result.x, 1, EPSILON);
	cr_assert_float_eq(result.y, 0, EPSILON);
	cr_assert_float_eq(result.z, 0, EPSILON);
}

/* Rotating a point around the z axis */
Test(transformations, rotation_around_z_axis)
{
	t_matrix	half_quarter;
	t_matrix	full_quarter;
	t_tuple		p;
	t_tuple		result;

	p = point(0.0, 1.0, 0.0);
	half_quarter = rotation_z(M_PI_4);
	full_quarter = rotation_z(M_PI_2);

	result = multiply_tp_mx(half_quarter, p);
	cr_assert_float_eq(result.x, -sqrt(2)/2, EPSILON);
	cr_assert_float_eq(result.y, sqrt(2)/2, EPSILON);
	cr_assert_float_eq(result.z, 0, EPSILON);

	result = multiply_tp_mx(full_quarter, p);
	cr_assert_float_eq(result.x, -1, EPSILON);
	cr_assert_float_eq(result.y, 0, EPSILON);
	cr_assert_float_eq(result.z, 0, EPSILON);
}

/* A shearing transformation moves x in proportion to z */
Test(transformations, shearing_x_in_y)
{
	t_matrix	transform;
	t_tuple		p;
	t_tuple		result;

	p = point(2.0, 3.0, 4.0);
	transform = shearing((t_shearing){1, 0}, (t_shearing){0}, (t_shearing){0});

	result = multiply_tp_mx(transform, p);
	cr_assert_float_eq(result.x, 5, EPSILON);
	cr_assert_float_eq(result.y, 3, EPSILON);
	cr_assert_float_eq(result.z, 4, EPSILON);
}

/* A shearing transformation moves y in proportion to x */
Test(transformations, shearing_x_in_z)
{
	t_matrix	transform;
	t_tuple		p;
	t_tuple		result;

	p = point(2.0, 3.0, 4.0);
	transform = shearing((t_shearing){0, 1}, (t_shearing){0}, (t_shearing){0});

	result = multiply_tp_mx(transform, p);
	cr_assert_float_eq(result.x, 6, EPSILON);
	cr_assert_float_eq(result.y, 3, EPSILON);
	cr_assert_float_eq(result.z, 4, EPSILON);
}

/* A shearing transformation moves y in proportion to z */
Test(transformations, shearing_y_in_x)
{
	t_matrix	transform;
	t_tuple		p;
	t_tuple		result;

	p = point(2.0, 3.0, 4.0);
	transform = shearing((t_shearing){0}, (t_shearing){1, 0}, (t_shearing){0});

	result = multiply_tp_mx(transform, p);
	cr_assert_float_eq(result.x, 2, EPSILON);
	cr_assert_float_eq(result.y, 5, EPSILON);
	cr_assert_float_eq(result.z, 4, EPSILON);
}

/* A shearing transformation moves z in proportion to x */
Test(transformations, shearing_y_in_z)
{
	t_matrix	transform;
	t_tuple		p;
	t_tuple		result;

	p = point(2.0, 3.0, 4.0);
	transform = shearing((t_shearing){0}, (t_shearing){0, 1}, (t_shearing){0});

	result = multiply_tp_mx(transform, p);
	cr_assert_float_eq(result.x, 2, EPSILON);
	cr_assert_float_eq(result.y, 7, EPSILON);
	cr_assert_float_eq(result.z, 4, EPSILON);
}

/* A shearing transformation moves z in proportion to y */
Test(transformations, shearing_z_in_x)
{
	t_matrix	transform;
	t_tuple		p;
	t_tuple		result;

	p = point(2.0, 3.0, 4.0);
	transform = shearing((t_shearing){0}, (t_shearing){0}, (t_shearing){1, 0});

	result = multiply_tp_mx(transform, p);
	cr_assert_float_eq(result.x, 2, EPSILON);
	cr_assert_float_eq(result.y, 3, EPSILON);
	cr_assert_float_eq(result.z, 6, EPSILON);
}

/* Individual transformations are applied in sequence */
Test(transformations, shearing_z_in_y)
{
	t_matrix	transform;
	t_tuple		p;
	t_tuple		result;

	p = point(2.0, 3.0, 4.0);
	transform = shearing((t_shearing){0}, (t_shearing){0}, (t_shearing){0, 1});

	result = multiply_tp_mx(transform, p);
	cr_assert_float_eq(result.x, 2, EPSILON);
	cr_assert_float_eq(result.y, 3, EPSILON);
	cr_assert_float_eq(result.z, 7, EPSILON);
}

/* Individual transformations are applied in sequence */
Test(transformations, transf_in_sequence)
{
	t_tuple		p;
	t_tuple		p2;
	t_tuple		p3;
	t_tuple		p4;
	t_matrix	a;
	t_matrix	b;
	t_matrix	c;

	p = point(1.0, 0.0, 1.0);
	a = rotation_x(M_PI_2);
	b = scaling(5.0, 5.0, 5.0);
	c = translation(10.0, 5.0, 7.0);

	// Apply rotation first
	p2 = multiply_tp_mx(a, p);
	cr_assert_float_eq(p2.x, 1, EPSILON);
	cr_assert_float_eq(p2.y, -1, EPSILON);
	cr_assert_float_eq(p2.z, 0, EPSILON);

	// Then apply scaling
	p3 = multiply_tp_mx(b, p2);
	cr_assert_float_eq(p3.x, 5, EPSILON);
	cr_assert_float_eq(p3.y, -5, EPSILON);
	cr_assert_float_eq(p3.z, 0, EPSILON);

	// Then apply translation
	p4 = multiply_tp_mx(c, p3);
	cr_assert_float_eq(p4.x, 15, EPSILON);
	cr_assert_float_eq(p4.y, 0, EPSILON);
	cr_assert_float_eq(p4.z, 7, EPSILON);
}

/* Chained transformations must be applied in reverse order */
Test(transformations, chained_transf_in_reverse)
{
	t_tuple		p;
	t_matrix	a;
	t_matrix	b;
	t_matrix	c;
	t_matrix	t;
	t_tuple		result;

	p = point(1.0, 0.0, 1.0);
	a = rotation_x(M_PI_2);
	b = scaling(5.0, 5.0, 5.0);
	c = translation(10.0, 5.0, 7.0);

	t = multiply_mx_mx(multiply_mx_mx(c, b), a);
	result = multiply_tp_mx(t, p);
	cr_assert_float_eq(result.x, 15, EPSILON);
	cr_assert_float_eq(result.y, 0, EPSILON);
	cr_assert_float_eq(result.z, 7, EPSILON);
}
