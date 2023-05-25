/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 09:49:29 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/24 13:03:43 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_bool	parse_double(t_scanner *scanner, double *result)
{
	if (scan_double(scanner))
	{
		*result = ft_atof(scanner->consume);
		return (TRUE);
	}
	return (FALSE);
}

t_bool	parse_light_ratio(t_scanner *scanner, double *light)
{
	if (!scan_double(scanner))
		return (FALSE);
	*light = ft_atof(scanner->consume);
	if (validate_range(*light, 0, 1))
		return (TRUE);
	set_error_state(scanner, INVALID_LIGHT INVALID_NUMBER);
	return (FALSE);
}

t_bool	parse_field_of_view(t_scanner *scanner, int *fov)
{
	if (!scan_integer(scanner))
		return (FALSE);
	*fov = ft_atoi(scanner->consume);
	if (validate_range(*fov, 0, 180))
		return (TRUE);
	set_error_state(scanner, INVALID_FOV INVALID_NUMBER);
	return (FALSE);
}

t_bool	parse_dimension(t_scanner *scanner, double *dimension)
{
	if (!scan_double(scanner))
		return (FALSE);
	*dimension = ft_atof(scanner->consume);
	if (*dimension >= 0)
		return (TRUE);
	set_error_state(scanner, INVALID_DIMENSION INVALID_NUMBER);
	return (FALSE);
}
