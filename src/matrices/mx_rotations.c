/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_rotations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:44:25 by yde-goes          #+#    #+#             */
/*   Updated: 2023/05/24 11:14:17 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrices.h"

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
