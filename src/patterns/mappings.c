/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mappings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:38:41 by yde-goes          #+#    #+#             */
/*   Updated: 2023/06/02 16:55:11 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "patterns.h"

void	texture_map(t_pattern *pattern, t_checker checkers, t_uv_map uv_map)
{
	pattern->texture_map.uv_pattern = checkers;
	pattern->texture_map.uv_map = uv_map;
}

t_checker	spherical_map(t_point point)
{
	double		theta;
	t_vector	vec;
	double		radius;
	double		phi;
	double		raw_u;

	theta = atan2(point.x, point.z);
	vec = vector(point.x, point.y, point.z);
	radius = magnitude(vec);
	phi = acos(point.y / radius);
	raw_u = theta / (2 * M_PI);
	return ((t_checker){
		.width = 1 - (raw_u + 0.5),
		.height = 1 - phi / M_PI,
		.color_a = {0},
		.color_b = {0}
	});
}

t_checker	planar_map(t_point point)
{
	double	v;

	v = fmod(point.z, 1.0);
	if (v < 0.0)
		v = 1.0 + v;
	return ((t_checker){
		.width = fmod(point.x, 1.0),
		.height = v,
		.color_a = {0},
		.color_b = {0}
	});
}

t_checker	cylindrical_map(t_point point)
{
	double	theta;
	double	raw_u;
	double	v;

	v = fmod(point.y, 1.0);
	if (v < 0.0)
		v = 1.0 + v;
	theta = atan2(point.x, point.z);
	raw_u = theta / (2 * M_PI);
	return ((t_checker){
		.width = 1 - (raw_u + 0.5),
		.height = v,
		.color_a = {0},
		.color_b = {0}
	});
}
