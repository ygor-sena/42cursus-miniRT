/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tuples.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 21:13:02 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/11 10:47:39 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "tuples.h"
#include "utils.h"

Test(tuples, create_a_tuple)
{
	t_tuple	a;

	a = tuple(4.2, -4.2, 3.2, 1.0);
	cr_assert(eq(flt, a.x, 4.2));
	cr_assert(eq(flt, a.y, -4.2));
	cr_assert(eq(flt, a.z, 3.2));
	cr_assert(eq(flt, a.w, 1.0));

	a = tuple(4.2, -4.2, 3.2, 0.0);
	cr_assert(eq(flt, a.x, 4.2));
	cr_assert(eq(flt, a.y, -4.2));
	cr_assert(eq(flt, a.z, 3.2));
	cr_assert(eq(flt, a.w, 0.0));
}

Test(tuples, create_a_point)
{
	t_tuple	a;

	a = point(4.2, -4.2, 3.2);
	cr_assert(eq(flt, a.x, 4.2));
	cr_assert(eq(flt, a.y, -4.2));
	cr_assert(eq(flt, a.z, 3.2));
	cr_assert(eq(flt, a.w, 1.0));
}

Test(tuples, create_a_vector)
{
	t_tuple	a;

	a = vector(4.2, -4.2, 3.2);
	cr_assert(eq(flt, a.x, 4.2));
	cr_assert(eq(flt, a.y, -4.2));
	cr_assert(eq(flt, a.z, 3.2));
	cr_assert(eq(flt, a.w, 0.0));
}

Test(tuples, adding_tuples)
{
	t_tuple	a;
	t_tuple	b;
	t_tuple	result;

	a = tuple(3, -2, 5, 1.0);
	b = tuple(-2, 3, 1, 0);
	result = add(a, b);
	cr_assert(eq(flt, result.x, 1));
	cr_assert(eq(flt, result.y, 1));
	cr_assert(eq(flt, result.z, 6));
	cr_assert(eq(flt, result.w, 1));
}

Test(tuples, subtracting_tuples)
{
	t_tuple	a;
	t_tuple	b;
	t_tuple	result;

	a = point(3, 2, 1);
	b = point(5, 6, 7);
	result = subtract(a, b);
	cr_assert(eq(flt, result.x, -2));
	cr_assert(eq(flt, result.y, -4));
	cr_assert(eq(flt, result.z, -6));

	a = point(3, 2, 1);
	b = vector(5, 6, 7);
	result = subtract(a, b);
	cr_assert(eq(flt, result.x, -2));
	cr_assert(eq(flt, result.y, -4));
	cr_assert(eq(flt, result.z, -6));

	a = vector(3, 2, 1);
	b = vector(5, 6, 7);
	result = subtract(a, b);
	cr_assert(eq(flt, result.x, -2));
	cr_assert(eq(flt, result.y, -4));
	cr_assert(eq(flt, result.z, -6));
}

Test(tuples, negating_tuples)
{
	t_tuple	result;

	result = negate(tuple(1, -2, 3, -4));
	cr_assert(eq(flt, result.x, -1));
	cr_assert(eq(flt, result.y, 2));
	cr_assert(eq(flt, result.z, -3));
	cr_assert(eq(flt, result.w, 4));
}

Test(tuples, multiplying_tuples)
{
	t_tuple	result;

	result = multiply(tuple(1, -2, 3, -4), 3.5);
	cr_assert(eq(flt, result.x, 3.5));
	cr_assert(eq(flt, result.y, -7));
	cr_assert(eq(flt, result.z, 10.5));
	cr_assert(eq(flt, result.w, -14));

	result = multiply(tuple(1, -2, 3, -4), 0.5);
	cr_assert(eq(flt, result.x, 0.5));
	cr_assert(eq(flt, result.y, -1));
	cr_assert(eq(flt, result.z, 1.5));
	cr_assert(eq(flt, result.w, -2));
}

Test(tuples, dividing_tuples)
{
	t_tuple	result;

	result = divide(tuple(1, -2, 3, -4), 2);
	cr_assert(eq(flt, result.x, 0.5));
	cr_assert(eq(flt, result.y, -1));
	cr_assert(eq(flt, result.z, 1.5));
	cr_assert(eq(flt, result.w, -2));
}

Test(tuples, get_magnitude)
{
	float	length;

	length = magnitude(vector(1, 0, 0));
	cr_assert(eq(flt, length, 1));

	length = magnitude(vector(0, 1, 0));
	cr_assert(eq(flt, length, 1));

	length = magnitude(vector(0, 0, 1));
	cr_assert(eq(flt, length, 1));

	length = magnitude(vector(1, 2, 3));
	cr_assert(eq(flt, length, sqrtf(14)));

	length = magnitude(vector(-1, -2, -3));
	cr_assert(eq(flt, length, sqrtf(14)));
}

Test(tuples, normalizing_vectors)
{
	t_tuple	v;
	t_tuple	normal;

	v = vector(4, 0, 0);
	normal = normalize(v);
	cr_assert(epsilon_eq(flt, magnitude(normal), 1, FLT_EPSILON));

	v = vector(1, 2, 3);
	normal = normalize(v);
	cr_assert(epsilon_eq(flt, magnitude(normal), 1, FLT_EPSILON));
}

Test(tuples, dot_product)
{
	t_tuple	a;
	t_tuple	b;
	float	result;

	a = vector(1, 2, 3);
	b = vector(2, 3, 4);
	result = dot(a, b);
	cr_assert(eq(flt, result, 20));
}

Test(tuples, cross_product)
{
	t_tuple	a;
	t_tuple	b;
	t_tuple	result;

	a = vector(1, 2, 3);
	b = vector(2, 3, 4);
	result = cross(a, b);
	cr_assert(eq(flt, result.x, -1));
	cr_assert(eq(flt, result.y, 2));
	cr_assert(eq(flt, result.z, -1));

	result = cross(b, a);
	cr_assert(eq(flt, result.x, 1));
	cr_assert(eq(flt, result.y, -2));
	cr_assert(eq(flt, result.z, 1));
}

/*	Reflecting a vector approaching at 45° */
Test(tuples, reflect_vector_45)
{
	t_tuple	v;
	t_tuple	n;
	t_tuple result;
	t_tuple	expect;

	v = vector(1, -1, 0);
	n = vector(0, 1, 0);
	result = reflect(v, n);
	expect = vector(1, 1, 0);

	cr_assert_float_eq(result.x, expect.x, EPSILON);
	cr_assert_float_eq(result.y, expect.y, EPSILON);
	cr_assert_float_eq(result.z, expect.z, EPSILON);
}

/*	Reflecting a vector off a slanted surface */
Test(tuples, reflect_vector_slanted_surface)
{
	t_tuple	v;
	t_tuple	n;
	t_tuple result;
	t_tuple	expect;
	float	coord;

	coord = sqrtf(2)/2.0;
	v = vector(0, -1, 0);
	n = vector(coord, coord, 0);
	result = reflect(v, n);
	expect = vector(1, 0, 0);

	cr_assert_float_eq(result.x, expect.x, EPSILON);
	cr_assert_float_eq(result.y, expect.y, EPSILON);
	cr_assert_float_eq(result.z, expect.z, EPSILON);
}
