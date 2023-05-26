/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:47:49 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/26 07:58:55 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"

t_shape	new_shape(void)
{
	return ((t_shape){
		.material = material(),
		.transform = get_identity_matrix(),
		.inverse = get_identity_matrix(),
		.transpose = get_identity_matrix(),
	});
}

void	set_transform(t_shape *shape, t_matrix transform)
{
	shape->transform = transform;
	shape->inverse = inverse(transform);
	shape->transpose = transpose(shape->inverse);
}

t_vector	normal_at(t_shape *shape, t_point world_point)
{
	t_point 	object_point;
	t_vector	object_normal;
	t_vector	world_normal;

	object_point = multiply_tp_mx(shape->inverse, world_point);
	object_normal = shape->normal_at(shape, object_point);
	world_normal = multiply_tp_mx(shape->transpose, object_normal);
	world_normal.w = 0.0;
	return (normalize(world_normal));
}
