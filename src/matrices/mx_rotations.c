/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_rotations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:44:25 by yde-goes          #+#    #+#             */
/*   Updated: 2023/03/27 11:23:14 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrices.h"

t_matrix	rotation_x(float rad)
{
	const float	sine = sin(rad);
	const float	cosine = cos(rad);
	const float	rotate[MAX][MAX] = {
	{1, 0, 0, 0},
	{0, cosine, -sine, 0},
	{0, sine, cosine, 0},
	{0, 0, 0, 1},
	};

	return (create_matrix(rotate, MAX));
}

t_matrix	rotation_y(float rad)
{
	const float	sine = sin(rad);
	const float	cosine = cos(rad);
	const float	rotate[MAX][MAX] = {
	{cosine, 0, sine, 0},
	{0, 1, 0, 0},
	{-sine, 0, cosine, 0},
	{0, 0, 0, 1},
	};

	return (create_matrix(rotate, MAX));
}

t_matrix	rotation_z(float rad)
{
	const float	sine = sin(rad);
	const float	cosine = cos(rad);
	const float	rotate[MAX][MAX] = {
	{cosine, -sine, 0, 0},
	{sine, cosine, 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1},
	};

	return (create_matrix(rotate, MAX));
}
