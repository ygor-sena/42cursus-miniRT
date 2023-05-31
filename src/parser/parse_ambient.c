/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:17:27 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/27 11:50:17 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#define DEGREES_TO_RADIANS 0.017453

t_bool	parse_ambient_light(t_scanner *scanner, t_scene *scene)
{
	double	intensity;
	t_color	lighting;

	if (!parse_light_ratio(scanner, &intensity))
		return (FALSE);
	if (!parse_color(scanner, &lighting))
		return (FALSE);
	if (!scan_newline(scanner))
		return (FALSE);
	scene->world.ambient = multiply_color(lighting, intensity);
	return (TRUE);
}

t_bool	parse_camera(t_scanner *scanner, t_scene *scene)
{
	int			fov;
	t_point		origin;
	t_vector	direction;
	t_camera	camera;

	if (!parse_position(scanner, &origin))
		return (FALSE);
	if (!parse_direction(scanner, &direction))
		return (FALSE);
	if (!parse_field_of_view(scanner, &fov))
		return (FALSE);
	if (!scan_newline(scanner))
		return (FALSE);
	camera = new_camera(SCREEN_WIDTH, SCREEN_HEIGHT, fov * DEGREES_TO_RADIANS);
	camera.transform = view_transform(origin, point(0, 1, 0), direction);
	camera.inverse = inverse(camera.transform);
	scene->camera = camera;
	return (TRUE);
}

t_bool	parse_light(t_scanner *scanner, t_scene *scene)
{
	t_point	origin;
	double	bright;
	t_color	color;
	t_light	light;

	if (!parse_position(scanner, &origin))
		return (FALSE);
	if (!parse_light_ratio(scanner, &bright))
		return (FALSE);
	if (!parse_color(scanner, &color))
		return (FALSE);
	if (!scan_newline(scanner))
		return (FALSE);
	color = multiply_color(color, bright);
	light = point_light(origin, color);
	add_light_to_world(&light, &scene->world);
	return (TRUE);
}
