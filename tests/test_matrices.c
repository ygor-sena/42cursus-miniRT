/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_matrices.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:33:50 by yde-goes          #+#    #+#             */
/*   Updated: 2023/04/11 14:29:37 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "matrices.h"
#include "tuples.h"
#include "utils.h"

/*	Constructing and inspecting a 4x4 matrix */
Test(matrices, create_matrix_4x4)
{
	t_matrix	m;

	const float	table[MAX][MAX] = {
		{1, 2, 3, 4},
		{5.5, 6.5, 7.5, 8.5},
		{9, 10, 11, 12},
		{13.5, 14.5, 15.5, 16.5},
	};

	m = create_matrix(table, MAX);
	cr_assert(eq(flt, m.matrix[0][0], 1));
	cr_assert(eq(flt, m.matrix[0][1], 2));
	cr_assert(eq(flt, m.matrix[0][2], 3));
	cr_assert(eq(flt, m.matrix[0][3], 4));

	cr_assert(eq(flt, m.matrix[1][0], 5.5));
	cr_assert(eq(flt, m.matrix[1][1], 6.5));
	cr_assert(eq(flt, m.matrix[1][2], 7.5));
	cr_assert(eq(flt, m.matrix[1][3], 8.5));

	cr_assert(eq(flt, m.matrix[2][0], 9));
	cr_assert(eq(flt, m.matrix[2][1], 10));
	cr_assert(eq(flt, m.matrix[2][2], 11));
	cr_assert(eq(flt, m.matrix[2][3], 12));

	cr_assert(eq(flt, m.matrix[3][0], 13.5));
	cr_assert(eq(flt, m.matrix[3][1], 14.5));
	cr_assert(eq(flt, m.matrix[3][2], 15.5));
	cr_assert(eq(flt, m.matrix[3][3], 16.5));
}

/*	Constructing and inspecting a 2x2 matrix */
Test(matrices, create_matrix_2x2)
{
	t_matrix	m;

	const float	table[MAX][MAX] = {
		{-3, 5},
		{1, -2},
	};

	m = create_matrix(table, 2);
	cr_assert(eq(flt, m.matrix[0][0], -3));
	cr_assert(eq(flt, m.matrix[0][1], 5));
	cr_assert(eq(flt, m.matrix[1][0], 1));
	cr_assert(eq(flt, m.matrix[1][1], -2));
}

/*	Constructing and inspecting a 3x3 matrix */
Test(matrices, create_matrix_3x3)
{
	t_matrix	m;

	const float	table[MAX][MAX] = {
		{-3, 5, 0},
		{1, -2, -7},
		{0, 1, 1},
	};

	m = create_matrix(table, 3);
	cr_assert(eq(flt, m.matrix[0][0], -3));
	cr_assert(eq(flt, m.matrix[0][1], 5));
	cr_assert(eq(flt, m.matrix[0][2], 0));

	cr_assert(eq(flt, m.matrix[1][0], 1));
	cr_assert(eq(flt, m.matrix[1][1], -2));
	cr_assert(eq(flt, m.matrix[1][2], -7));

	cr_assert(eq(flt, m.matrix[2][0], 0));
	cr_assert(eq(flt, m.matrix[2][1], 1));
	cr_assert(eq(flt, m.matrix[2][2], 1));
}

/*	Matrix equality with identical matrices */
Test(matrices, is_equal_matrix)
{
	t_matrix	a;
	t_matrix	b;
	int			result;

	const float	table_a[MAX][MAX] = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 8, 7, 6},
		{5, 4, 3, 2},
	};

	const float	table_b[MAX][MAX] = {
		{2, 3, 4, 5},
		{6, 7, 8, 9},
		{8, 7, 6, 5},
		{4, 3, 2, 1},
	};

	a = create_matrix(table_a, MAX);
	b = create_matrix(table_b, MAX);

	result = compare_matrix(a, b);
	cr_assert(ne(int, result, 0));
}

/*	Matrix equality with different matrices */
Test(matrices, is_not_equal_matrix)
{
	t_matrix	a;
	t_matrix	b;
	int			result;

	const float	table_a[MAX][MAX] = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 8, 7, 6},
		{5, 4, 3, 2},
	};

	const float	table_b[MAX][MAX] = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 8, 7, 6},
		{5, 4, 3, 2},
	};

	a = create_matrix(table_a, MAX);
	b = create_matrix(table_b, MAX);

	result = compare_matrix(a, b);
	cr_assert(eq(int, result, 0));
}

/*	Multiplying two matrices */
Test(matrices, multiply_mx_mx)
{
	t_matrix	a;
	t_matrix	b;
	t_matrix	c;

	const float	table_a[MAX][MAX] = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 8, 7, 6},
		{5, 4, 3, 2},
	};

	const float	table_b[MAX][MAX] = {
		{-2, 1, 2, 3},
		{3, 2, 1, -1},
		{4, 3, 6, 5},
		{1, 2, 7, 8},
	};

	a = create_matrix(table_a, MAX);
	b = create_matrix(table_b, MAX);
	c = multiply_mx_mx(a, b);

	cr_assert(eq(flt, c.matrix[0][0], 20));
	cr_assert(eq(flt, c.matrix[0][1], 22));
	cr_assert(eq(flt, c.matrix[0][2], 50));
	cr_assert(eq(flt, c.matrix[0][3], 48));

	cr_assert(eq(flt, c.matrix[1][0], 44));
	cr_assert(eq(flt, c.matrix[1][1], 54));
	cr_assert(eq(flt, c.matrix[1][2], 114));
	cr_assert(eq(flt, c.matrix[1][3], 108));

	cr_assert(eq(flt, c.matrix[2][0], 40));
	cr_assert(eq(flt, c.matrix[2][1], 58));
	cr_assert(eq(flt, c.matrix[2][2], 110));
	cr_assert(eq(flt, c.matrix[2][3], 102));

	cr_assert(eq(flt, c.matrix[3][0], 16));
	cr_assert(eq(flt, c.matrix[3][1], 26));
	cr_assert(eq(flt, c.matrix[3][2], 46));
	cr_assert(eq(flt, c.matrix[3][3], 42));
}

/*	Multipliying 4x4 matrix by a tuple */
Test(matrices, multiply_tp_mx)
{
	t_matrix	a;
	t_tuple		b;
	t_tuple		c;

	const float	table_a[MAX][MAX] = {
		{1, 2, 3, 4},
		{2, 4, 4, 2},
		{8, 6, 4, 1},
		{0, 0, 0, 1},
	};

	a = create_matrix(table_a, MAX);
	b = tuple(1, 2, 3, 1);
	c = multiply_tp_mx(a, b);

	cr_assert(eq(flt, c.x, 18));
	cr_assert(eq(flt, c.y, 24));
	cr_assert(eq(flt, c.z, 33));
	cr_assert(eq(flt, c.w, 1));
}

/*	Multipliying a 4x4 matrix by the identity matrix */
Test(matrices, multiply_by_identity_matrix)
{
	t_matrix	a;
	t_matrix	id;
	t_matrix	c;

	const float	table_a[MAX][MAX] = {
		{0, 1, 2, 4},
		{1, 2, 4, 8},
		{2, 4, 8, 16},
		{4, 8, 16, 32},
	};

	const float	table_id[MAX][MAX] = {
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1},
	};

	a = create_matrix(table_a, MAX);
	id = create_matrix(table_id, MAX);
	c = multiply_mx_mx(a, id);

	cr_assert(eq(flt, c.matrix[0][0], 0));
	cr_assert(eq(flt, c.matrix[0][1], 1));
	cr_assert(eq(flt, c.matrix[0][2], 2));
	cr_assert(eq(flt, c.matrix[0][3], 4));

	cr_assert(eq(flt, c.matrix[1][0], 1));
	cr_assert(eq(flt, c.matrix[1][1], 2));
	cr_assert(eq(flt, c.matrix[1][2], 4));
	cr_assert(eq(flt, c.matrix[1][3], 8));

	cr_assert(eq(flt, c.matrix[2][0], 2));
	cr_assert(eq(flt, c.matrix[2][1], 4));
	cr_assert(eq(flt, c.matrix[2][2], 8));
	cr_assert(eq(flt, c.matrix[2][3], 16));

	cr_assert(eq(flt, c.matrix[3][0], 4));
	cr_assert(eq(flt, c.matrix[3][1], 8));
	cr_assert(eq(flt, c.matrix[3][2], 16));
	cr_assert(eq(flt, c.matrix[3][3], 32));
}

/*	Transposing a matrix */
Test(matrices, transpose)
{
	t_matrix	a;
	t_matrix	c;

	const float	table_a[MAX][MAX] = {
		{0, 9, 3, 0},
		{9, 8, 0, 8},
		{1, 8, 5, 3},
		{0, 0, 5, 8},
	};

	a = create_matrix(table_a, MAX);
	c = transpose(a);
	//c = create_matrix(table_a, MAX);
	//transpose(&c);

	cr_assert(eq(flt, c.matrix[0][0], 0));
	cr_assert(eq(flt, c.matrix[0][1], 9));
	cr_assert(eq(flt, c.matrix[0][2], 1));
	cr_assert(eq(flt, c.matrix[0][3], 0));

	cr_assert(eq(flt, c.matrix[1][0], 9));
	cr_assert(eq(flt, c.matrix[1][1], 8));
	cr_assert(eq(flt, c.matrix[1][2], 8));
	cr_assert(eq(flt, c.matrix[1][3], 0));

	cr_assert(eq(flt, c.matrix[2][0], 3));
	cr_assert(eq(flt, c.matrix[2][1], 0));
	cr_assert(eq(flt, c.matrix[2][2], 5));
	cr_assert(eq(flt, c.matrix[2][3], 5));

	cr_assert(eq(flt, c.matrix[3][0], 0));
	cr_assert(eq(flt, c.matrix[3][1], 8));
	cr_assert(eq(flt, c.matrix[3][2], 3));
	cr_assert(eq(flt, c.matrix[3][3], 8));
}

/*
*	Transposition of an identity matrix should be an..
*	identity matrix!
*/
Test(matrices, transpose_of_identity_matrix)
{
	t_matrix	a;
	t_matrix	id;

	const float	table_id[MAX][MAX] = {
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1},
	};

	a = create_matrix(table_id, MAX);
	id = transpose(a);

	cr_assert(eq(flt, id.matrix[0][0], 1));
	cr_assert(eq(flt, id.matrix[0][1], 0));
	cr_assert(eq(flt, id.matrix[0][2], 0));
	cr_assert(eq(flt, id.matrix[0][3], 0));

	cr_assert(eq(flt, id.matrix[1][0], 0));
	cr_assert(eq(flt, id.matrix[1][1], 1));
	cr_assert(eq(flt, id.matrix[1][2], 0));
	cr_assert(eq(flt, id.matrix[1][3], 0));

	cr_assert(eq(flt, id.matrix[2][0], 0));
	cr_assert(eq(flt, id.matrix[2][1], 0));
	cr_assert(eq(flt, id.matrix[2][2], 1));
	cr_assert(eq(flt, id.matrix[2][3], 0));

	cr_assert(eq(flt, id.matrix[3][0], 0));
	cr_assert(eq(flt, id.matrix[3][1], 0));
	cr_assert(eq(flt, id.matrix[3][2], 0));
	cr_assert(eq(flt, id.matrix[3][3], 1));
}

/* 	Calculating the determinant of a 2x2 matrix */
Test(matrices, determinant_2x2)
{
	t_matrix	a;
	int			result;

	const float	table_a[MAX][MAX] = {
		{1, 5},
		{-3, 2},
	};

	a = create_matrix(table_a, 2);

	result = get_determinant(a);
	cr_assert(eq(int, result, 17));
}

/*	A submatrix of a 3x3 matrix is a 2x2 matrix */
Test(matrices, submatrix_of_3x3)
{
	t_matrix	a;
	t_matrix	result;

	const float	table_a[MAX][MAX] = {
		{1, 5, 0},
		{-3, 2, 7},
		{0, 6, -3},
	};
	
	a = create_matrix(table_a, 3);
	result = get_submatrix(a, 0, 2);

	cr_assert(eq(flt, result.matrix[0][0], -3));
	cr_assert(eq(flt, result.matrix[0][1], 2));

	cr_assert(eq(flt, result.matrix[1][0], 0));
	cr_assert(eq(flt, result.matrix[1][1], 6));
}

/*	A submatrix of a 4x4 matrix is a 3x3 matrix */
Test(matrices, submatrix_of_4x4)
{
	t_matrix	a;
	t_matrix	result;

	const float	table_a[MAX][MAX] = {
		{-6, 1, 1, 6},
		{-8, 5, 8, 6},
		{-1, 0, 8, 2},
		{-7, 1, -1, 1},
	};
	
	a = create_matrix(table_a, 4);
	result = get_submatrix(a, 2, 1);

	cr_assert(eq(flt, result.matrix[0][0], -6));
	cr_assert(eq(flt, result.matrix[0][1], 1));
	cr_assert(eq(flt, result.matrix[0][2], 6));

	cr_assert(eq(flt, result.matrix[1][0], -8));
	cr_assert(eq(flt, result.matrix[1][1], 8));
	cr_assert(eq(flt, result.matrix[1][2], 6));

	cr_assert(eq(flt, result.matrix[2][0], -7));
	cr_assert(eq(flt, result.matrix[2][1], -1));
	cr_assert(eq(flt, result.matrix[2][2], 1));
}

/*	Calculating a minor of a 3x3 matrix */
Test(matrices, minor_of_3x3)
{
	t_matrix	a;
	float		result;

	const float	table_a[MAX][MAX] = {
		{3, 5, 0},
		{2, -1, 7},
		{6, -1, 5},
	};
	
	a = create_matrix(table_a, 3);
	
	result = get_minor(a, 0, 0);
	cr_assert(eq(flt, result, 2));

	result = get_minor(a, 1, 0);
	cr_assert(eq(flt, result, 25));
}

/*	Calculating a cofactor of a 3x3 matrix */
Test(matrices, cofactor_of_3x3)
{
	t_matrix	a;
	float		result;

	const float	table_a[MAX][MAX] = {
		{3, 5, 0},
		{2, -1, 7},
		{6, -1, 5},
	};
	
	a = create_matrix(table_a, 3);

	result = get_cofactor(a, 0, 0);
	cr_assert(eq(flt, result, 2));

	result = get_cofactor(a, 1, 0);
	cr_assert(eq(flt, result, -25));
}

/*	Calculating the determinant of a 3x3 matrix */
Test(matrices, determinant_of_3x3)
{
	t_matrix	a;
	float		result;

	const float	table_a[MAX][MAX] = {
		{1, 2, 6},
		{-5, 8, -4},
		{2, 6, 4},
	};
	
	a = create_matrix(table_a, 3);

	result = get_cofactor(a, 0, 0);
	cr_assert(eq(flt, result, 56));

	result = get_cofactor(a, 0, 1);
	cr_assert(eq(flt, result, 12));
	
	result = get_cofactor(a, 0, 2);
	cr_assert(eq(flt, result, -46));

	result = get_determinant(a);
	cr_assert(eq(flt, result, -196));
}

/*	Calculating the determinant of a 4x4 matrix */
Test(matrices, determinant_of_4x4)
{
	t_matrix	a;
	float		result;

	const float	table_a[MAX][MAX] = {
		{-2, -8, 3, 5},
		{-3, 1, 7, 3},
		{1, 2, -9, 6},
		{-6, 7, 7, -9},
	};
	
	a = create_matrix(table_a, 4);

	result = get_cofactor(a, 0, 0);
	cr_assert(eq(flt, result, 690));

	result = get_cofactor(a, 0, 1);
	cr_assert(eq(flt, result, 447));
	
	result = get_cofactor(a, 0, 2);
	cr_assert(eq(flt, result, 210));

	result = get_cofactor(a, 0, 3);
	cr_assert(eq(flt, result, 51));

	result = get_determinant(a);
	cr_assert(eq(flt, result, -4071));
}

/*	Testing an invertible matrix for invertibility */
Test(matrices, is_invertible_4x4)
{
	t_matrix	a;
	float		result;

	const float	table_a[MAX][MAX] = {
		{6, 4, 4, 4},
		{5, 5, 7, 6},
		{4, -9, 3, -7},
		{9, 1, 7, -6},
	};
	
	a = create_matrix(table_a, 4);

	result = get_determinant(a);
	cr_assert(eq(flt, result, -2120));
	cr_assert(eq(int, true, is_invertible(a)));
}

/*	Testing a noninvertible matrix for invertibility */
Test(matrices, is_not_invertible_4x4)
{
	t_matrix	a;
	float		result;

	const float	table_a[MAX][MAX] = {
		{-4, 2, -2, -3},
		{9, 6, 2, 6},
		{0, -5, 1, -5},
		{0, 0, 0, 0},
	};
	
	a = create_matrix(table_a, 4);

	result = get_determinant(a);
	cr_assert(eq(flt, result, 0));
	cr_assert(eq(int, false, is_invertible(a)));
}

/*	Calculating the inverse of a matrix */
Test(matrices, get_inverse_1)
{
	t_matrix	a;
	t_matrix	b;
	float		result;

	const float	table_a[MAX][MAX] = {
		{-5, 2, 6, -8},
		{1, -5, 1, 8},
		{7, 7, -6, -7},
		{1, -3, 7, 4},
	};
	
	a = create_matrix(table_a, 4);
	b = inverse(a);
	
	result = get_determinant(a);
	cr_assert(eq(flt, result, 532));

	result = get_cofactor(a, 2, 3);
	cr_assert(eq(flt, result, -160));
	cr_assert(eq(flt, b.matrix[3][2], (float) -160/532));

	result = get_cofactor(a, 3, 2);
	cr_assert(eq(flt, result, 105));
	cr_assert(eq(flt, b.matrix[2][3], (float) 105/532));

	cr_assert_float_eq(b.matrix[0][0], 0.21805, EPSILON);
	cr_assert_float_eq(b.matrix[0][1], 0.45113, EPSILON);
	cr_assert_float_eq(b.matrix[0][2], 0.24060, EPSILON);
	cr_assert_float_eq(b.matrix[0][3], -0.04511, EPSILON);

	cr_assert_float_eq(b.matrix[1][0], -0.80827, EPSILON);
	cr_assert_float_eq(b.matrix[1][1], -1.45677, EPSILON);
	cr_assert_float_eq(b.matrix[1][2], -0.44361, EPSILON);
	cr_assert_float_eq(b.matrix[1][3], 0.52068, EPSILON);

	cr_assert_float_eq(b.matrix[2][0], -0.07895, EPSILON);
	cr_assert_float_eq(b.matrix[2][1], -0.22368, EPSILON);
	cr_assert_float_eq(b.matrix[2][2], -0.05263, EPSILON);
	cr_assert_float_eq(b.matrix[2][3], 0.19737, EPSILON);

	cr_assert_float_eq(b.matrix[3][0], -0.52256, EPSILON);
	cr_assert_float_eq(b.matrix[3][1], -0.81391, EPSILON);
	cr_assert_float_eq(b.matrix[3][2], -0.30075, EPSILON);
	cr_assert_float_eq(b.matrix[3][3], 0.30639, EPSILON);
}

/*	Calculating the inverse of another matrix */
Test(matrices, get_inverse_2)
{
	t_matrix	a;
	t_matrix	b;

	const float	table_a[MAX][MAX] = {
		{8, -5, 9, 2},
		{7, 5, 6, 1},
		{-6, 0, 9, 6},
		{-3, 0, -9, -4},
	};
	
	a = create_matrix(table_a, 4);
	b = inverse(a);

	cr_assert_float_eq(b.matrix[0][0], -0.15385, EPSILON);
	cr_assert_float_eq(b.matrix[0][1], -0.15385, EPSILON);
	cr_assert_float_eq(b.matrix[0][2], -0.28205, EPSILON);
	cr_assert_float_eq(b.matrix[0][3], -0.53846, EPSILON);

	cr_assert_float_eq(b.matrix[1][0], -0.07692, EPSILON);
	cr_assert_float_eq(b.matrix[1][1], 0.12308, EPSILON);
	cr_assert_float_eq(b.matrix[1][2], 0.02564, EPSILON);
	cr_assert_float_eq(b.matrix[1][3], 0.03077, EPSILON);

	cr_assert_float_eq(b.matrix[2][0], 0.35897, EPSILON);
	cr_assert_float_eq(b.matrix[2][1], 0.35897, EPSILON);
	cr_assert_float_eq(b.matrix[2][2], 0.43590, EPSILON);
	cr_assert_float_eq(b.matrix[2][3], 0.92308, EPSILON);

	cr_assert_float_eq(b.matrix[3][0], -0.69231, EPSILON);
	cr_assert_float_eq(b.matrix[3][1], -0.69231, EPSILON);
	cr_assert_float_eq(b.matrix[3][2], -0.76923, EPSILON);
	cr_assert_float_eq(b.matrix[3][3], -1.92308, EPSILON);
}

/*	Calculating the inverse of a third matrix */
Test(matrices, get_inverse_3)
{
	t_matrix	a;
	t_matrix	b;

	const float	table_a[MAX][MAX] = {
		{9, 3, 0, 9},
		{-5, -2, -6, -3},
		{-4, 9, 6, 4},
		{-7, 6, 6, 2},
	};
	
	a = create_matrix(table_a, 4);
	b = inverse(a);

	cr_assert_float_eq(b.matrix[0][0], -0.04074, EPSILON);
	cr_assert_float_eq(b.matrix[0][1], -0.07778, EPSILON);
	cr_assert_float_eq(b.matrix[0][2], 0.14444, EPSILON);
	cr_assert_float_eq(b.matrix[0][3], -0.22222, EPSILON);

	cr_assert_float_eq(b.matrix[1][0], -0.07778, EPSILON);
	cr_assert_float_eq(b.matrix[1][1], 0.03333, EPSILON);
	cr_assert_float_eq(b.matrix[1][2], 0.36667, EPSILON);
	cr_assert_float_eq(b.matrix[1][3], -0.33333, EPSILON);

	cr_assert_float_eq(b.matrix[2][0], -0.02901, EPSILON);
	cr_assert_float_eq(b.matrix[2][1], -0.14630, EPSILON);
	cr_assert_float_eq(b.matrix[2][2], -0.10926, EPSILON);
	cr_assert_float_eq(b.matrix[2][3], 0.12963, EPSILON);

	cr_assert_float_eq(b.matrix[3][0], 0.17778, EPSILON);
	cr_assert_float_eq(b.matrix[3][1], 0.06667, EPSILON);
	cr_assert_float_eq(b.matrix[3][2], -0.26667, EPSILON);
	cr_assert_float_eq(b.matrix[3][3], 0.33333, EPSILON);
}

/*	Multiplying a product by its inverse */
Test(matrices, mult_product_by_its_inverse)
{
	t_matrix	a;
	t_matrix	b;
	t_matrix	c;
	t_matrix	result;

	const float	table_a[MAX][MAX] = {
		{3, -9, 7, 3},
		{3, -8, 2, -9},
		{-4, 4, 4, 1},
		{-6, 5, -1, 1},
	};

	const float	table_b[MAX][MAX] = {
		{8, 2, 2, 2},
		{3, -1, 7, 0},
		{7, 0, 5, 4},
		{6, -2, 0, 5},
	};
	
	a = create_matrix(table_a, 4);
	b = create_matrix(table_b, 4);
	c = multiply_mx_mx(a, b);
	result = multiply_mx_mx(c, inverse(b));

	cr_assert_float_eq(result.matrix[0][0], 3, EPSILON);
	cr_assert_float_eq(result.matrix[0][1], -9, EPSILON);
	cr_assert_float_eq(result.matrix[0][2], 7, EPSILON);
	cr_assert_float_eq(result.matrix[0][3], 3, EPSILON);

	cr_assert_float_eq(result.matrix[1][0], 3, EPSILON);
	cr_assert_float_eq(result.matrix[1][1], -8, EPSILON);
	cr_assert_float_eq(result.matrix[1][2], 2, EPSILON);
	cr_assert_float_eq(result.matrix[1][3], -9, EPSILON);

	cr_assert_float_eq(result.matrix[2][0], -4, EPSILON);
	cr_assert_float_eq(result.matrix[2][1], 4, EPSILON);
	cr_assert_float_eq(result.matrix[2][2], 4, EPSILON);
	cr_assert_float_eq(result.matrix[2][3], 1, EPSILON);

	cr_assert_float_eq(result.matrix[3][0], -6, EPSILON);
	cr_assert_float_eq(result.matrix[3][1], 5, EPSILON);
	cr_assert_float_eq(result.matrix[3][2], -1, EPSILON);
	cr_assert_float_eq(result.matrix[3][3], 1, EPSILON);
}
