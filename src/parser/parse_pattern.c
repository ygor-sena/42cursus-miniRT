/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pattern.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:11:46 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/06/08 19:09:30 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#define STRIPED 0
#define CHECKERED 1
#define BUMPMAP 2

static t_bool	scan_pattern(t_scanner *scanner, int *type);
static void		load_checkerboard(t_shape *shape);

t_bool	parse_pattern(t_scanner *scanner, t_shape *shape)
{
	int			type;
	t_color		color_a;
	t_color		color_b;

	if (!scan_pattern(scanner, &type))
		return (TRUE);
	if (type == BUMPMAP)
		return (parse_texture(scanner, shape));
	if (!parse_color(scanner, &color_a))
		return (FALSE);
	if (!parse_color(scanner, &color_b))
		return (FALSE);
	shape->material.pattern = new_pattern(color_a, color_b);
	if (type == CHECKERED)
		load_checkerboard(shape);
	return (TRUE);
}

static void	load_checkerboard(t_shape *shape)
{
	t_checker	checker;
	t_pattern	pattern;

	pattern = shape->material.pattern;
	checker = uv_checkers(16, 8, pattern.a, pattern.b);
	shape->checker = checker;
	shape->material.pattern.pattern_at = checkered_at;
	texture_map(&shape->material.pattern, shape->checker, shape->map);
}

static t_bool	scan_pattern(t_scanner *scanner, int *type)
{
	skip_whitespace(scanner);
	if (ft_strncmp(scanner->current, "checkered", 9) == 0)
	{
		*type = CHECKERED;
		scanner->current += 9;
		return (TRUE);
	}
	if (ft_strncmp(scanner->current, "striped", 7) == 0)
	{
		*type = STRIPED;
		scanner->current += 7;
		return (TRUE);
	}
	if (ft_strncmp(scanner->current, "bumpmap", 7) == 0)
	{
		*type = BUMPMAP;
		scanner->current += 7;
		return (TRUE);
	}
	skip_whitespace(scanner);
	return (FALSE);
}
