/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:28:08 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/03/18 14:46:30 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CANVAS_H
# define CANVAS_H

typedef struct s_color
{
	float	red;
	float	green;
	float	blue;
}	t_color;

t_color	new_color(float red, float green, float blue);
t_color	add_color(t_color a, t_color b);
t_color	subtract_color(t_color a, t_color b);
t_color	multiply_color(t_color color, float scalar);
t_color	hadamard_product(t_color a, t_color b);

#endif
