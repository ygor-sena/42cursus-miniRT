/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_view_transform.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:28:50 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/18 16:01:24 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "utils.h"

Test(view_transformation, transform_default_orientation)
{
	t_tuple		from;
	t_tuple		to;
	t_tuple		up;
	t_matrix	t;
	int			result;

	from = point(0, 0, 0);
	to = point(0, 0, -1);
	up = vector(0, 1, 0);
	t = view_transform(from, to, up);

	result = compare_matrix(t, get_identity_matrix());
	cr_assert(eq(i32, result, 0));
}

Test(view_transformation, looking_in_positive_z)
{
	t_tuple		from;
	t_tuple		to;
	t_tuple		up;
	t_matrix	t;
	int			result;

	from = point(0, 0, 0);
	to = point(0, 0, 1);
	up = vector(0, 1, 0);
	t = view_transform(from, to, up);

	result = compare_matrix(t, scaling(-1, 1, -1));
	cr_assert(eq(i32, result, 0));
}

Test(view_transformation, moves_the_world)
{
	t_tuple		from;
	t_tuple		to;
	t_tuple		up;
	t_matrix	t;
	int			result;

	from = point(0, 0, 8);
	to = point(0, 0, 0);
	up = vector(0, 1, 0);
	t = view_transform(from, to, up);

	result = compare_matrix(t, translation(0, 0, -8));
	cr_assert(eq(i32, result, 0));
}

Test(view_transformation, arbitrary_transformation)
{
	t_tuple		from;
	t_tuple		to;
	t_tuple		up;
	t_matrix	t;

	const float	expected[MAX][MAX] = {
		{-0.50709, 0.50709,  0.67612, -2.36643},
		{ 0.76772, 0.60609,  0.12122, -2.82843},
		{-0.35857, 0.59761, -0.71714,  0.00000},
		{ 0.00000, 0.00000,  0.00000,  1.00000},
	};

	from = point(1, 3, 2);
	to = point(4, -2, 8);
	up = vector(1, 1, 0);
	t = view_transform(from, to, up);

	for (size_t i = 0; i < t.size; i++)
	{
		for (size_t j = 0; j < t.size; j++)
			cr_assert_float_eq(t.matrix[i][j], expected[i][j], EPSILON);
	}
}
