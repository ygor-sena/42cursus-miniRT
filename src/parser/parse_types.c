/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:02:39 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/14 17:13:02 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_bool	match(t_scanner *scanner, char expected);
static t_bool	match_shape(t_scanner *scanner, char *expected);

t_token	parse_type(t_scanner *scanner)
{
	if (match(scanner, 'A'))
		return (TOKEN_AMBIENT_LIGHT);
	if (match(scanner, 'C'))
		return (TOKEN_CAMERA);
	if (match(scanner, 'L'))
		return (TOKEN_LIGHT);
	if (match_shape(scanner, "sp"))
		return (TOKEN_SPHERE);
	if (match_shape(scanner, "pl"))
		return (TOKEN_PLANE);
	if (match_shape(scanner, "cy"))
		return (TOKEN_CYLINDER);
	if (match(scanner, '#'))
		return (TOKEN_COMMENT);
	if (match(scanner, '\n'))
		return (TOKEN_NEWLINE);
	return (TOKEN_ERROR);
}

static t_bool	match(t_scanner *scanner, char expected)
{
	if (*scanner->current != expected)
		return (FALSE);
	advance(scanner);
	return (TRUE);
}

static t_bool	match_shape(t_scanner *scanner, char *expected)
{
	if (match(scanner, expected[0]))
	{
		if (match(scanner, expected[1]))
			return (TRUE);
		return (FALSE);
	}
	return (FALSE);
}
