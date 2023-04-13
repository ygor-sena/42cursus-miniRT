/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:16:46 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/11 14:19:09 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"

t_ray	new_ray(t_point origin, t_vector direction)
{
	return ((t_ray){
		origin, direction
	});
}

t_point	position(t_ray ray, float distance)
{
	return (add(ray.origin, multiply(ray.direction, distance)));
}

t_ray	transform(t_ray r, t_matrix m)
{
	return (
		new_ray(
			multiply_tp_mx(m, r.origin),
			multiply_tp_mx(m, r.direction))
	);
}
