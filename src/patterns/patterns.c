/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:22:30 by yde-goes          #+#    #+#             */
/*   Updated: 2023/05/19 20:03:38 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"

t_pattern	new_pattern(t_color a, t_color b)
{
	return ((t_pattern){
		.has_pattern = TRUE,
		.pattern_at = stripe_at,
		.a = new_color(a.red, a.green, a.blue),
		.b = new_color(b.red, b.green, b.blue)
	});
}

t_color	stripe_at(t_pattern pattern, t_tuple world_point)
{
	if ((int)floor(world_point.x) % 2 == 0)
		return (pattern.a);
	return (pattern.b);
}

t_color	checkered_at(t_pattern pattern, t_tuple world_point)
{
	if ((int)(floor(world_point.x) + floor(world_point.y)
		+ floor(world_point.z)) % 2 == 0)
		return (pattern.a);
	return (pattern.b);
}

t_color	pattern_at_shape(t_pattern pattern, t_shape *shape, t_tuple world_point)
{
	t_tuple	object_point;
	t_tuple	pattern_point;

	object_point = multiply_tp_mx(inverse(shape->transform), world_point);
	pattern_point = multiply_tp_mx(inverse(pattern.transform), object_point);
	return (pattern.pattern_at(pattern, pattern_point));
}

void	set_pattern_transform(t_pattern *pattern, t_matrix transform)
{
	pattern->transform = transform;
}
