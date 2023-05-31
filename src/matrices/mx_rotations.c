/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_rotations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:44:25 by yde-goes          #+#    #+#             */
/*   Updated: 2023/05/30 16:49:02 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrices.h"

static void	calculate_rotation_angles(t_vector vec, double *x, double *z);

t_matrix	rotation_matrix(t_vector vector)
{
	double		x_angle;
	double		z_angle;
	t_matrix	rotate_z;
	t_matrix	rotate_x;
	t_matrix	full_rotation;

	calculate_rotation_angles(vector, &x_angle, &z_angle);
	rotate_z = rotation_z(z_angle);
	rotate_x = rotation_x(x_angle);
	full_rotation = multiply_mx_mx(rotate_z, rotate_x);
	return (full_rotation);
}

/**
 * @brief Calculates the rotation angles for a given vector.
 *
 * @param vec The vector for which the rotation angles will be calculated.
 * @param x A pointer to the variable that will store the rotation angle
 *          around the x-axis.
 * @param z A pointer to the variable that will store the rotation angle
 *          around the z-axis.
 */
static void	calculate_rotation_angles(t_vector vec, double *x, double *z)
{
	double	ratio;

	ratio = sqrt((vec.x * vec.x) + (vec.y * vec.y));
	if (0.0 == ratio)
		*z = M_PI_2;
	else
		*z = acos(vec.y / ratio);
	*x = acos(ratio);
}

t_matrix	rotation_x(double rad)
{
	const double	sine = sin(rad);
	const double	cosine = cos(rad);
	const double	rotate[MAX][MAX] = {
	{1, 0, 0, 0},
	{0, cosine, -sine, 0},
	{0, sine, cosine, 0},
	{0, 0, 0, 1},
	};

	return (create_matrix(rotate, MAX));
}

t_matrix	rotation_y(double rad)
{
	const double	sine = sin(rad);
	const double	cosine = cos(rad);
	const double	rotate[MAX][MAX] = {
	{cosine, 0, sine, 0},
	{0, 1, 0, 0},
	{-sine, 0, cosine, 0},
	{0, 0, 0, 1},
	};

	return (create_matrix(rotate, MAX));
}

t_matrix	rotation_z(double rad)
{
	const double	sine = sin(rad);
	const double	cosine = cos(rad);
	const double	rotate[MAX][MAX] = {
	{cosine, -sine, 0, 0},
	{sine, cosine, 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1},
	};

	return (create_matrix(rotate, MAX));
}
