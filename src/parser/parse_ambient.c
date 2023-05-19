/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:17:27 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/19 16:45:48 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	add_light_to_world(t_light *light, t_world *world)
{
	world->lights = ft_realloc(
			world->lights, sizeof(t_shape) * (world->light_count + 1));
	world->lights[world->light_count++] = *light;
}

// TODO: precisa ser analisado depois das formas
t_bool	parse_ambient_light(t_scanner *scanner, t_scene *scene)
{
	float	intensity;
	t_color	lighting;

	(void) scene;
	if (!parse_light_ratio(scanner, &intensity))
		return (FALSE);
	if (!parse_color(scanner, &lighting))
		return (FALSE);
	if (!scan_newline(scanner))
		return (FALSE);
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
	camera = new_camera(400, 400, fov * (M_PI / 180.0));
	camera.transform = view_transform(origin, direction, vector(0, 1, 0));
	scene->camera = camera;
	return (TRUE);
}

t_bool	parse_light(t_scanner *scanner, t_scene *scene)
{
	t_point	origin;
	float	bright;
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
