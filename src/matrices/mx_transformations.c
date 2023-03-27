/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_transformations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:44:35 by yde-goes          #+#    #+#             */
/*   Updated: 2023/03/27 11:23:19 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrices.h"

t_matrix	translation(float x, float y, float z)
{
	const float	transl[MAX][MAX] = {
	{1, 0, 0, x},
	{0, 1, 0, y},
	{0, 0, 1, z},
	{0, 0, 0, 1},
	};

	return (create_matrix(transl, MAX));
}

t_matrix	scaling(float x, float y, float z)
{
	const float	scale[MAX][MAX] = {
	{x, 0, 0, 0},
	{0, y, 0, 0},
	{0, 0, z, 0},
	{0, 0, 0, 1},
	};

	return (create_matrix(scale, MAX));
}

t_matrix	shearing(t_shearing x, t_shearing y, t_shearing z)
{
	const float	shear[MAX][MAX] = {
	{1, x.p1, x.p2, 0},
	{y.p1, 1, y.p2, 0},
	{z.p1, z.p2, 1, 0},
	{0, 0, 0, 1},
	};

	return (create_matrix(shear, MAX));
}
