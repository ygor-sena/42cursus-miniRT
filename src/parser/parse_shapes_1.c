/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:11:42 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/30 18:01:04 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_bool	parse_sphere(t_scanner *scanner, t_scene *scene)
{
	t_shape		shape;
	t_matrix	scale;
	t_matrix	transform;
	t_point		origin;
	double		radius;

	shape = new_sphere();
	if (!parse_position(scanner, &origin))
		return (FALSE);
	if (!parse_dimension(scanner, &radius))
		return (FALSE);
	if (!parse_color(scanner, &shape.material.color))
		return (FALSE);
	if (!parse_pattern(scanner, &shape))
		return (FALSE);
	if (!scan_newline(scanner))
		return (FALSE);
	radius /= 2;
	scale = scaling(radius, radius, radius);
	transform = translation(origin.x, origin.y, origin.z);
	set_transform(&shape, multiply_mx_mx(transform, scale));
	add_object_to_world(&shape, &scene->world);
	return (TRUE);
}

t_bool	parse_plane(t_scanner *scanner, t_scene *scene)
{
	t_shape		shape;
	t_vector	direction;
	t_point		origin;
	t_matrix	translate;
	t_matrix	rotate;

	shape = new_plane();
	if (!parse_position(scanner, &origin))
		return (FALSE);
	if (!parse_direction(scanner, &direction))
		return (FALSE);
	if (!parse_color(scanner, &shape.material.color))
		return (FALSE);
	if (!parse_pattern(scanner, &shape))
		return (FALSE);
	if (!scan_newline(scanner))
		return (FALSE);
	translate = translation(origin.x, origin.y, origin.z);
	rotate = rotation_matrix(direction);
	set_transform(&shape, multiply_mx_mx(translate, rotate));
	add_object_to_world(&shape, &scene->world);
	return (TRUE);
}