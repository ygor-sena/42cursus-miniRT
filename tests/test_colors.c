/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:41:36 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/09 12:38:04 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

Test(colors, create_colors)
{
	t_color	c;

	c = new_color(1.5, -1.7, 0.7);
	cr_assert(eq(flt, c.red, 1.5));
	cr_assert(eq(flt, c.green, -1.7));
	cr_assert(eq(flt, c.blue, 0.7));
}

Test(colors, add_colors)
{
	t_color	c1;
	t_color	c2;
	t_color	result;

	c1 = new_color(0.9, 0.6, 0.75);
	c2 = new_color(0.7, 0.1, 0.25);
	result = add_color(c1, c2);
	cr_assert_float_eq(result.red, 1.6, EPSILON);
	cr_assert_float_eq(result.green, 0.7, EPSILON);
	cr_assert_float_eq(result.blue, 1.0, EPSILON);
}

Test(colors, subtract_colors)
{
	t_color	c1;
	t_color	c2;
	t_color	result;

	c1 = new_color(0.9, 0.6, 0.75);
	c2 = new_color(0.7, 0.1, 0.25);
	result = subtract_color(c1, c2);
	cr_assert_float_eq(result.red, 0.2, EPSILON);
	cr_assert_float_eq(result.green, 0.5, EPSILON);
	cr_assert_float_eq(result.blue, 0.50, EPSILON);
}

Test(colors, multiply_colors_by_scalar)
{
	t_color	c1;
	t_color	c2;
	t_color	result;

	c1 = new_color(1, 0.2, 0.4);
	c2 = new_color(0.9, 1, 0.1);
	result = hadamard_product(c1, c2);
	cr_assert_float_eq(result.red, 0.9, EPSILON);
	cr_assert_float_eq(result.green, 0.2, EPSILON);
	cr_assert_float_eq(result.blue, 0.04, EPSILON);
}
