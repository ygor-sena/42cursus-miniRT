/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_grouped.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:08:40 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/18 08:37:01 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_bool	parse_color_component(t_scanner *scanner, float *color);
static t_bool	parse_direction_component(t_scanner *scanner, float *coord);

// <color> ::= <int> "," <int> "," <int>
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

// <position> ::= <float> "," <float> "," <float>
t_bool	parse_position(t_scanner *scanner, t_point *position)
{
	if (!parse_float(scanner, &position->x))
		return (FALSE);
	if (!scan_comma(scanner))
		return (FALSE);
	if (!parse_float(scanner, &position->y))
		return (FALSE);
	if (!scan_comma(scanner))
		return (FALSE);
	if (!parse_float(scanner, &position->z))
		return (FALSE);
	return (TRUE);
}

// <direction> ::= <float> "," <float> "," <float>
t_bool	parse_direction(t_scanner *scanner, t_vector *direction)
{
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

static t_bool	parse_color_component(t_scanner *scanner, float *color)
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

static t_bool	parse_direction_component(t_scanner *scanner, float *coord)
{
	if (!scan_float(scanner))
		return (FALSE);
	*coord = ft_atof(scanner->consume);
	if (validate_range(*coord, -1.0, 1.0))
		return (TRUE);
	set_error_state(scanner, INVALID_VECTOR INVALID_NUMBER);
	return (FALSE);
}
