/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_scanner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:00:08 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/14 15:31:03 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

Test(scanner, scan_integer)
{
	t_scanner	scanner;

	init_scanner(&scanner, "42");
	cr_assert(eq(i32, scan_integer(&scanner), TRUE));

	init_scanner(&scanner, "-42");
	cr_assert(eq(i32, scan_integer(&scanner), TRUE));

	init_scanner(&scanner, "+42");
	cr_assert(eq(i32, scan_integer(&scanner), TRUE));

	init_scanner(&scanner, "   -42");
	cr_assert(eq(i32, scan_integer(&scanner), TRUE));

	init_scanner(&scanner, "   +42");
	cr_assert(eq(i32, scan_integer(&scanner), TRUE));

	init_scanner(&scanner, "--42");
	cr_assert(eq(i32, scan_integer(&scanner), FALSE));

	init_scanner(&scanner, "   --42");
	cr_assert(eq(i32, scan_integer(&scanner), FALSE));
}

Test(scanner, scan_float)
{
	t_scanner	scanner;

	init_scanner(&scanner, "3.14159");
	cr_assert(eq(i32, scan_float(&scanner), TRUE));

	init_scanner(&scanner, "-3.14159");
	cr_assert(eq(i32, scan_float(&scanner), TRUE));

	init_scanner(&scanner, "+3.14159");
	cr_assert(eq(i32, scan_float(&scanner), TRUE));

	init_scanner(&scanner, "   -3.14159");
	cr_assert(eq(i32, scan_float(&scanner), TRUE));

	init_scanner(&scanner, "   +3.14159");
	cr_assert(eq(i32, scan_float(&scanner), TRUE));

	init_scanner(&scanner, "--3.14159");
	cr_assert(eq(i32, scan_float(&scanner), FALSE));

	init_scanner(&scanner, "++3.14159");
	cr_assert(eq(i32, scan_float(&scanner), FALSE));

	init_scanner(&scanner, "     ++3.14159");
	cr_assert(eq(i32, scan_float(&scanner), FALSE));
}

Test(scanner, scan_newline)
{
	t_scanner	scanner;

	init_scanner(&scanner, "                        \n");
	cr_assert(eq(i32, scan_newline(&scanner), TRUE));

	init_scanner(&scanner, "            !           \n");
	cr_assert(eq(i32, scan_newline(&scanner), FALSE));
}
