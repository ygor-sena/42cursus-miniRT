/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:22:30 by yde-goes          #+#    #+#             */
/*   Updated: 2023/06/08 19:34:53 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"
#include "patterns.h"

t_pattern	new_pattern(t_color a, t_color b)
{
	return ((t_pattern){
		.has_pattern = TRUE,
		.pattern_at = stripe_at,
		.a = new_color(a.red, a.green, a.blue),
		.b = new_color(b.red, b.green, b.blue),
		.texture_map.uv_pattern = uv_checkers(0, 0, a, b),
		.texture_map.uv_map = planar_map,
		.texture_map.canvas = NULL,
		.transform = get_identity_matrix(),
		.inverse = get_identity_matrix(),
		.transpose = get_identity_matrix()
	});
}

t_color	stripe_at(t_pattern pattern, t_point world_point)
{
	if ((int)floor(world_point.x) % 2 == 0)
		return (pattern.a);
	return (pattern.b);
}

t_color	checkered_at(t_pattern pattern, t_point world_point)
{
	t_checker	uv;

	uv = pattern.texture_map.uv_map(world_point);
	return (
		uv_pattern_at(
			pattern.texture_map.uv_pattern,
			uv.width,
			uv.height
		));
}

t_color	pattern_at_shape(t_pattern pattern, t_shape *shape, t_point world_point)
{
	t_point	object_point;
	t_point	pattern_point;

	object_point = multiply_tp_mx(shape->inverse, world_point);
	pattern_point = multiply_tp_mx(pattern.inverse, object_point);
	return (pattern.pattern_at(pattern, pattern_point));
}

void	set_pattern_transform(t_pattern *pattern, t_matrix transform)
{
	pattern->transform = transform;
	pattern->inverse = inverse(transform);
	pattern->transpose = transpose(pattern->inverse);
}
