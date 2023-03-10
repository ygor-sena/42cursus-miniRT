/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 21:36:26 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/08/05 12:46:24 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

static void	parse_flags(const char **format, t_param *spec);
static void	parse_width(const char **format, t_param *spec);
static void	parse_precision(const char **format, t_param *spec);

void	parse_spec(const char *format, t_param *spec)
{
	spec->init = format++;
	clean_info(spec);
	parse_flags(&format, spec);
	parse_width(&format, spec);
	parse_precision(&format, spec);
	spec->code = *format;
	spec->end = format + 1;
	spec->next = find_spec(spec->end);
}

static void	parse_flags(const char **format, t_param *spec)
{
	t_flag	*flags;
	t_flag	set_flag;

	flags = flag_array();
	set_flag = flags[(unsigned)**format];
	if (set_flag == NULL)
		return ;
	set_flag(spec);
	(*format)++;
	parse_flags(format, spec);
}

static void	parse_width(const char **format, t_param *spec)
{
	if (ft_isdigit(**format))
		spec->width = read_nbr(format);
}

static void	parse_precision(const char **format, t_param *spec)
{
	if (**format == '.')
	{
		(*format)++;
		spec->flags[ZERO] = FALSE;
		spec->precision = read_nbr(format);
	}
}
