/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:11:15 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/11 22:03:51 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H

# include "world.h"

typedef enum e_token_type
{
	TOKEN_AMBIENT_LIGHT,
	TOKEN_CAMERA,
	TOKEN_LIGHT,
	TOKEN_SPHERE,
	TOKEN_PLANE,
	TOKEN_CYLINDER,
	TOKEN_FLOAT,
	TOKEN_INT,
	TOKEN_COLOR,
	TOKEN_POSITION,
	TOKEN_DIRECTION,
	TOKEN_SIGN,
	TOKEN_DIGIT,
	TOKEN_NEWLINE,
	TOKEN_COMMENT,
	TOKEN_ERROR
}	t_token_type;

typedef struct s_scanner
{
	const char	*start;
	const char	*consume;
	const char	*current;
	const char	*message;
	int			line;
}	t_scanner;

double	ft_atof(const char *nptr);

#endif // !PARSER_H
