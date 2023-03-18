/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 14:01:46 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/08/05 12:27:17 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/printer.h"

static int	print_null(t_param *spec);
static int	put_string_justified(t_param *spec, char *string, int strlen);

int	out_string(t_param *spec, va_list args)
{
	char	*string;
	int		strlen;
	int		written;

	written = 0;
	string = va_arg(args, char *);
	if (string == NULL)
		return (print_null(spec));
	strlen = ft_strlen(string);
	if (spec->precision != -1 && spec->precision < strlen)
		strlen = spec->precision;
	spec->width -= strlen;
	written = put_string_justified(spec, string, strlen);
	return (written);
}

static int	put_string_justified(t_param *spec, char *string, int strlen)
{
	int		written;

	written = 0;
	if (spec->flags[LEFT])
	{
		written += put_string(string, strlen);
		written += put_padding(spec);
		return (written);
	}
	written += put_padding(spec);
	written += put_string(string, strlen);
	return (written);
}

static int	print_null(t_param *spec)
{
	char	*null;
	int		strlen;
	int		written;

	written = 0;
	null = "(null)";
	strlen = 6;
	if (spec->precision == -1 || spec->precision >= strlen)
	{
		spec->width -= strlen;
		written = put_string_justified(spec, null, strlen);
	}
	else
		written = put_string_justified(spec, "", 0);
	return (written);
}
