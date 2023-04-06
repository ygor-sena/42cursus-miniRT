/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 18:16:46 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/06 10:39:56 by mdias-ma         ###   ########.fr       */
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
			multiply_tuple_matrix(m, r.origin),
			multiply_tuple_matrix(m, r.direction))
	);
}
