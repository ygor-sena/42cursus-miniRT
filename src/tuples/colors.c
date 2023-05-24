/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:24:30 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/24 11:15:16 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuples.h"

t_color	new_color(double red, double green, double blue)
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

t_color	multiply_color(t_color color, double scalar)
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
