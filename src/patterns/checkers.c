/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 09:45:15 by yde-goes          #+#    #+#             */
/*   Updated: 2023/06/02 16:54:56 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "patterns.h"

t_checker	uv_checkers(double width, double height, t_color a, t_color b)
{
	return ((t_checker){
		.width = width,
		.height = height,
		.color_a = new_color(a.red, a.green, a.blue),
		.color_b = new_color(b.red, b.green, b.blue)
	});
}

t_color	uv_pattern_at(t_checker checkers, double u, double v)
{
	int	u2;
	int	v2;

	u2 = floor(u * checkers.width);
	v2 = floor(v * checkers.height);
	if ((u2 + v2) % 2 == 0)
		return (checkers.color_a);
	return (checkers.color_b);
}
