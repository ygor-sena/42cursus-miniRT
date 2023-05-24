/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_grouped.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:08:40 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/24 13:16:07 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_bool	parse_color_component(t_scanner *scanner, double *color);
static t_bool	parse_direction_component(t_scanner *scanner, double *coord);

t_bool	parse_color(t_scanner *scanner, t_color *color)
{
	if (!parse_color_component(scanner, &color->red))
		return (FALSE);
	if (!scan_comma(scanner))
		return (FALSE);
	if (!parse_color_component(scanner, &color->green))
		return (FALSE);
	if (!scan_comma(scanner))
		return (FALSE);
	if (!parse_color_component(scanner, &color->blue))
		return (FALSE);
	return (TRUE);
}

t_bool	parse_position(t_scanner *scanner, t_point *position)
{
	*position = point(0, 0, 0);
	if (!parse_double(scanner, &position->x))
		return (FALSE);
	if (!scan_comma(scanner))
		return (FALSE);
	if (!parse_double(scanner, &position->y))
		return (FALSE);
	if (!scan_comma(scanner))
		return (FALSE);
	if (!parse_double(scanner, &position->z))
		return (FALSE);
	return (TRUE);
}

t_bool	parse_direction(t_scanner *scanner, t_vector *direction)
{
	*direction = vector(0, 0, 0);
	if (!parse_direction_component(scanner, &direction->x))
		return (FALSE);
	if (!scan_comma(scanner))
		return (FALSE);
	if (!parse_direction_component(scanner, &direction->y))
		return (FALSE);
	if (!scan_comma(scanner))
		return (FALSE);
	if (!parse_direction_component(scanner, &direction->z))
		return (FALSE);
	return (TRUE);
}

static t_bool	parse_color_component(t_scanner *scanner, double *color)
{
	if (!scan_integer(scanner))
		return (FALSE);
	*color = ft_atoi(scanner->consume);
	if (validate_range(*color, 0, 255))
	{
		*color /= 255;
		return (TRUE);
	}
	set_error_state(scanner, INVALID_COLOR INVALID_NUMBER);
	return (FALSE);
}

static t_bool	parse_direction_component(t_scanner *scanner, double *coord)
{
	if (!scan_double(scanner))
		return (FALSE);
	*coord = ft_atof(scanner->consume);
	if (validate_range(*coord, -1.0, 1.0))
		return (TRUE);
	set_error_state(scanner, INVALID_VECTOR INVALID_NUMBER);
	return (FALSE);
}
