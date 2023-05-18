/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_atof.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:56:28 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/14 12:34:46 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

Test(atof, string_to_float)
{
	char	*str = "3.14159";
	float	result;
	float	expected;

	result = ft_atof(str);
	expected = atof(str);
	cr_assert_float_eq(result, expected, EPSILON);

	str = "3.14159,8";
	result = ft_atof(str);
	expected = atof(str);
	cr_assert_float_eq(result, expected, EPSILON);

	str = "-20 ";
	result = ft_atof(str);
	expected = atof(str);
	cr_assert_float_eq(result, expected, EPSILON);
}

Test(atof, string_with_plus_sign)
{
	char	*str = "+3.14159";
	float	result;
	float	expected;

	result = ft_atof(str);
	expected = atof(str);
	cr_assert_float_eq(result, expected, EPSILON);
}

Test(atof, string_with_double_plus_sign)
{
	char	*str = "++3.14159";
	float	result;
	float	expected;

	result = ft_atof(str);
	expected = atof(str);
	cr_assert_float_eq(result, expected, EPSILON);
}

Test(atof, string_with_minus_sign)
{
	char	*str = "-3.14159";
	float	result;
	float	expected;

	result = ft_atof(str);
	expected = atof(str);
	cr_assert_float_eq(result, expected, EPSILON);
}

Test(atof, string_with_double_minus_sign)
{
	char	*str = "--3.14159";
	float	result;
	float	expected;

	result = ft_atof(str);
	expected = atof(str);
	cr_assert_float_eq(result, expected, EPSILON);
}

Test(atof, skip_spaces)
{
	char	*str = "    -3.14159";
	float	result;
	float	expected;

	result = ft_atof(str);
	expected = atof(str);
	cr_assert_float_eq(result, expected, EPSILON);
}
