/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:18:30 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/06/11 09:55:30 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

Test(parser, double_with_valid_input)
{
	t_scanner	scanner;
	double		result;
	double		expected;

	expected = 3.14159;
	init_scanner(&scanner, "3.14159");
	parse_double(&scanner, &result);
	cr_assert(eq(flt, result, expected));
}

Test(parser, double_with_invalid_character)
{
	t_scanner	scanner;
	double		result;
	t_bool		success;
	int			error_column;

	init_scanner(&scanner, "I000.1");
	success = parse_double(&scanner, &result);
	error_column = get_error_column(&scanner);
	cr_assert(eq(i32, success, FALSE));
	cr_assert(eq(i32, error_column, 0));
}

Test(parser, color_without_spaces)
{
	t_scanner	scanner;
	t_color		result;
	t_color		expected;
	t_bool		success;
	double		value;

	value = 10.0 / 255;
	init_scanner(&scanner, "10,10,10");
	expected = new_color(value, value, value);
	success = parse_color(&scanner, &result);

	cr_assert(eq(i32, success, TRUE));
	cr_assert(eq(flt, result.red, expected.red));
	cr_assert(eq(flt, result.green, expected.green));
	cr_assert(eq(flt, result.blue, expected.blue));
}

Test(parser, color_with_multiple_spaces)
{
	t_scanner	scanner;
	t_color		result;
	t_color		expected;
	t_bool		success;
	double		value;

	value = 10.0 / 255;
	init_scanner(&scanner, "10,     10,10");
	expected = new_color(value, value, value);
	success = parse_color(&scanner, &result);

	cr_assert(eq(i32, success, TRUE));
	cr_assert(eq(flt, result.red, expected.red));
	cr_assert(eq(flt, result.green, expected.green));
	cr_assert(eq(flt, result.blue, expected.blue));
}

Test(parser, color_with_invalid_character)
{
	t_scanner	scanner;
	t_color		result;
	t_bool		success;
	int			error_column;

	init_scanner(&scanner, "10, I0,10");
	success = parse_color(&scanner, &result);
	error_column = get_error_column(&scanner);
	cr_assert(eq(i32, success, FALSE));
	cr_assert(eq(i32, error_column, 4));
}

Test(parser, color_out_of_range)
{
	t_scanner	scanner;
	t_color		result;
	t_bool		success;
	int			error_column;

	init_scanner(&scanner, "10, 256, 10");
	success = parse_color(&scanner, &result);
	error_column = get_error_column(&scanner);
	cr_assert(eq(i32, success, FALSE));
	cr_assert(eq(i32, error_column, 4));
}

Test(parser, color_without_a_comma)
{
	t_scanner	scanner;
	t_color		result;
	t_bool		success;
	int			error_column;

	init_scanner(&scanner, "10 10, 10");
	success = parse_color(&scanner, &result);
	error_column = get_error_column(&scanner);
	cr_assert(eq(i32, success, FALSE));
	cr_assert(eq(i32, error_column, 3));
}

Test(parser, position_with_valid_input)
{
	t_scanner	scanner;
	t_point		result;
	t_point		expected;
	t_bool		success;

	init_scanner(&scanner, "0.3, 1.7, 16.4");
	expected = point(0.3, 1.7, 16.4);
	success = parse_position(&scanner, &result);
	cr_assert(eq(i32, success, TRUE));
	cr_assert(eq(flt, result.x, expected.x));
	cr_assert(eq(flt, result.y, expected.y));
	cr_assert(eq(flt, result.z, expected.z));
}

Test(parser, position_without_a_comma)
{
	t_scanner	scanner;
	t_point		result;
	t_bool		success;
	int			error_column;

	init_scanner(&scanner, "0.3  1.7, 16.4");
	success = parse_position(&scanner, &result);
	error_column = get_error_column(&scanner);
	cr_assert(eq(i32, success, FALSE));
	cr_assert(eq(i32, error_column, 5));
}

Test(parser, direction_with_valid_input)
{
	t_scanner	scanner;
	t_vector	result;
	t_vector	expected;
	t_bool		success;

	init_scanner(&scanner, "-1.0, 0.0, 0.0");
	expected = vector(-1.0, 0.0, 0.0);
	success = parse_direction(&scanner, &result);
	cr_assert(eq(i32, success, TRUE));
	cr_assert(eq(flt, result.x, expected.x));
	cr_assert(eq(flt, result.y, expected.y));
	cr_assert(eq(flt, result.z, expected.z));
}

Test(parser, direction_without_a_comma)
{
	t_scanner	scanner;
	t_point		result;
	t_bool		success;
	int			error_column;

	init_scanner(&scanner, "0.0003  1.0, 16.4");
	success = parse_direction(&scanner, &result);
	error_column = get_error_column(&scanner);
	cr_assert(eq(i32, success, FALSE));
	cr_assert(eq(i32, error_column, 8));
}

Test(parser, direction_out_of_range)
{
	t_scanner	scanner;
	t_vector	result;
	t_bool		success;
	int			error_column;

	init_scanner(&scanner, "-1.3, 0.7, 0.4");
	success = parse_direction(&scanner, &result);
	error_column = get_error_column(&scanner);
	cr_assert(eq(i32, success, FALSE));
	cr_assert(eq(i32, error_column, 0));
}

Test(parser, field_of_view_with_valid_input)
{
	t_scanner	scanner;
	double		result;
	double		expected;

	expected = 180;
	init_scanner(&scanner, "180");
	parse_double(&scanner, &result);
	cr_assert(eq(flt, result, expected));
}

Test(parser, field_of_view_out_of_range)
{
	t_scanner	scanner;
	int			result;
	t_bool		success;
	int			error_column;

	init_scanner(&scanner, "190");
	success = parse_field_of_view(&scanner, &result);
	error_column = get_error_column(&scanner);
	cr_assert(eq(i32, success, FALSE));
	cr_assert(eq(i32, error_column, 0));
}

Test(parser, light_ratio_with_valid_input)
{
	t_scanner	scanner;
	double		result;
	double		expected;

	expected = -1;
	init_scanner(&scanner, "-1");
	parse_light_ratio(&scanner, &result);
	cr_assert(eq(flt, result, expected));
}

Test(parser, light_ratio_out_of_range)
{
	t_scanner	scanner;
	double		result;
	t_bool		success;
	int			error_column;

	init_scanner(&scanner, "-2");
	success = parse_light_ratio(&scanner, &result);
	error_column = get_error_column(&scanner);
	cr_assert(eq(i32, success, FALSE));
	cr_assert(eq(i32, error_column, 0));
}

Test(parser, dimension_with_valid_input)
{
	t_scanner	scanner;
	double		result;
	double		expected;

	expected = 42;
	init_scanner(&scanner, "42");
	parse_light_ratio(&scanner, &result);
	cr_assert(eq(flt, result, expected));
}

Test(parser, dimension_out_of_range)
{
	t_scanner	scanner;
	double		result;
	t_bool		success;
	int			error_column;

	init_scanner(&scanner, "-2");
	success = parse_light_ratio(&scanner, &result);
	error_column = get_error_column(&scanner);
	cr_assert(eq(i32, success, FALSE));
	cr_assert(eq(i32, error_column, 0));
}
