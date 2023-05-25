/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:01:27 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/24 11:15:04 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuples.h"

double	magnitude(t_tuple v)
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
	double	length;

	length = magnitude(v);
	return ((t_tuple){
		v.x / length,
		v.y / length,
		v.z / length,
		v.w / length,
	});
}

double	dot(t_tuple a, t_tuple b)
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

t_tuple	reflect(t_tuple in, t_tuple normal)
{
	return (
		subtract(
			in, multiply(
				multiply(normal, 2.0), dot(in, normal))));
}
