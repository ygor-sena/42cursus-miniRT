/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:01:27 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/03/17 13:01:54 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuples.h"

float	magnitude(t_tuple v)
{
	return (
		sqrtf(
			v.x * v.x
			+ v.y * v.y
			+ v.z * v.z
			+ v.w * v.w
		)
	);
}

t_tuple	normalize(t_tuple v)
{
	float	length;

	length = magnitude(v);
	return ((t_tuple){
		v.x / length,
		v.y / length,
		v.z / length,
		v.w / length,
	});
}

float	dot(t_tuple a, t_tuple b)
{
	return (
		a.x * b.x
		+ a.y * b.y
		+ a.z * b.z
		+ a.w * b.w
	);
}

t_tuple	cross(t_tuple a, t_tuple b)
{
	return (
		vector(a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x)
	);
}
