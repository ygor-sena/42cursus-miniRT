/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:13:58 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/16 13:17:58 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_bool	parse_element(t_scanner *scanner, t_scene *scene)
{
	t_token		type;

	type = parse_type(scanner);
	if (type == TOKEN_AMBIENT_LIGHT)
		return (parse_ambient_light(scanner, scene));
	if (type == TOKEN_CAMERA)
		return (parse_camera(scanner, scene));
	if (type == TOKEN_LIGHT)
		return (parse_light(scanner, scene));
	if (type == TOKEN_SPHERE)
		return (parse_sphere(scanner, scene));
	if (type == TOKEN_PLANE)
		return (parse_plane(scanner, scene));
	if (type == TOKEN_CYLINDER)
		return (parse_cylinder(scanner, scene));
	if (type == TOKEN_COMMENT)
		return (parse_comment(scanner));
	if (type == TOKEN_NEWLINE)
		return (TRUE);
	return (FALSE);
}

t_bool	parse_comment(t_scanner *scanner)
{
	while (*scanner->current != '\n')
		advance(scanner);
	if (!scan_newline(scanner))
		return (FALSE);
	return (TRUE);
}

void	add_to_world(t_shape *shape, t_world *world)
{
	world->objects = ft_realloc(
			world->objects, sizeof(t_shape) * (world->object_count + 1));
	world->objects[world->object_count++] = *shape;
}
