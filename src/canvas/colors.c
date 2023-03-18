/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:24:30 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/03/18 10:25:55 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "canvas.h"

t_color	new_color(float red, float green, float blue)
{
	return ((t_color){
		red, green, blue,
	});
}

t_color	add_color(t_color a, t_color b)
{
	return ((t_color){
		a.red + b.red,
		a.green + b.green,
		a.blue + b.blue
	});
}

t_color	subtract_color(t_color a, t_color b)
{
	return ((t_color){
		a.red - b.red,
		a.green - b.green,
		a.blue - b.blue
	});
}

t_color	multiply_color(t_color color, float scalar)
{
	return ((t_color){
		color.red * scalar,
		color.green * scalar,
		color.blue * scalar,
	});
}

t_color	hadamard_product(t_color a, t_color b)
{
	return ((t_color){
		a.red * b.red,
		a.green * b.green,
		a.blue * b.blue
	});
}
