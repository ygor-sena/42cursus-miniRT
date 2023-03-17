/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:25:26 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/03/17 13:25:50 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuples.h"

t_tuple	add(t_tuple a, t_tuple b)
{
	return ((t_tuple){
		a.x + b.x,
		a.y + b.y,
		a.z + b.z,
		a.w + b.w,
	});
}

t_tuple	subtract(t_tuple a, t_tuple b)
{
	return ((t_tuple){
		a.x - b.x,
		a.y - b.y,
		a.z - b.z,
		a.w - b.w,
	});
}

t_tuple	negate(t_tuple a)
{
	return ((t_tuple){
		a.x * -1,
		a.y * -1,
		a.z * -1,
		a.w * -1,
	});
}

t_tuple	multiply(t_tuple a, float scalar)
{
	return ((t_tuple){
		a.x * scalar,
		a.y * scalar,
		a.z * scalar,
		a.w * scalar,
	});
}

t_tuple	divide(t_tuple a, float scalar)
{
	return ((t_tuple){
		a.x / scalar,
		a.y / scalar,
		a.z / scalar,
		a.w / scalar,
	});
}
