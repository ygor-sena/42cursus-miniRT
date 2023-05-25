/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_transform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:30:15 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/24 11:14:33 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

static t_matrix	orient_xform(t_tuple forward, t_tuple left, t_tuple true_up);

t_matrix	view_transform(t_tuple from, t_tuple to, t_tuple up)
{
	t_tuple		forward;
	t_tuple		left;
	t_tuple		true_up;
	t_matrix	orientation;

	forward = normalize(subtract(to, from));
	left = cross(forward, normalize(up));
	true_up = cross(left, forward);
	orientation = orient_xform(forward, left, true_up);
	return (multiply_mx_mx(
			orientation,
			translation(-from.x, -from.y, -from.z))
	);
}

static t_matrix	orient_xform(t_tuple forward, t_tuple left, t_tuple true_up)
{
	const double	table[MAX][MAX] = {
	{left.x, left.y, left.z, 0},
	{true_up.x, true_up.y, true_up.z, 0},
	{-forward.x, -forward.y, -forward.z, 0},
	{0, 0, 0, 1},
	};

	return (create_matrix(table, MAX));
}
