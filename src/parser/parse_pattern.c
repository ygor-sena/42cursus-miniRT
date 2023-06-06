/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pattern.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:11:46 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/06/06 13:17:55 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#define STRIPED 0
#define CHECKERED 1

t_bool	scan_pattern(t_scanner *scanner, int *type);
void	make_checkerboard(t_shape *shape);

t_bool	parse_pattern(t_scanner *scanner, t_shape *shape)
{
	int			type;
	t_color		color_a;
	t_color		color_b;
	t_pattern	pattern;

	if (scan_pattern(scanner, &type))
	{
		if (!parse_color(scanner, &color_a))
			return (FALSE);
		if (!parse_color(scanner, &color_b))
			return (FALSE);
		pattern = new_pattern(color_a, color_b);
		shape->material.pattern = pattern;
		shape->material.pattern.pattern_at = stripe_at;
		if (type == CHECKERED)
			make_checkerboard(shape);
		set_pattern_transform(
			&shape->material.pattern,
			translation(0.1, 0.1, 0.1));
	}
	return (TRUE);
}

void	make_checkerboard(t_shape *shape)
{
	shape->material.pattern.pattern_at = checkered_at;
	texture_map(&shape->material.pattern, shape->checker, shape->map);
}

t_bool	scan_pattern(t_scanner *scanner, int *type)
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
	skip_whitespace(scanner);
	return (FALSE);
}
