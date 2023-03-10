/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 17:26:03 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/11/14 10:19:26 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/printer.h"

static int	left_justify(t_param *spec, char *string, int strlen);
static int	right_justify(t_param *spec, char *string, int strlen);

int	put_string(const char *string, int length)
{
	(void)!write(STDOUT_FILENO, string, length);
	return (length);
}

int	put_format(t_param *spec, va_list args)
{
	t_out	*types;
	t_out	put_conversion;

	types = conversion_array();
	put_conversion = types[(unsigned)spec->code];
	if (put_conversion == NULL)
		return (put_string(spec->init, (spec->end - spec->init)));
	return (put_conversion(spec, args));
}

int	put_number_justified(t_param *spec, char *string, int strlen)
{
	int	written;

	written = 0;
	if (spec->flags[LEFT])
		written += left_justify(spec, string, strlen);
	else
		written += right_justify(spec, string, strlen);
	return (written);
}

static int	left_justify(t_param *spec, char *string, int strlen)
{
	int		written;
	int		temp;

	written = 0;
	if (spec->prefix[0])
		written += put_string(spec->prefix, spec->prefix_len);
	spec->width -= (strlen + spec->precision + spec->prefix_len);
	spec->pad = '0';
	if (spec->precision > 0)
	{
		temp = spec->width;
		spec->width = spec->precision;
		written += put_padding(spec);
		spec->width = temp;
	}
	spec->pad = ' ';
	written += put_string(string, strlen);
	written += put_padding(spec);
	return (written);
}

static int	right_justify(t_param *spec, char *string, int strlen)
{
	int		written;

	written = 0;
	spec->width -= (strlen + spec->precision + spec->prefix_len);
	if (spec->flags[ZERO] == FALSE)
	{
		spec->pad = ' ';
		written += put_padding(spec);
	}
	if (spec->prefix[0])
		written += put_string(spec->prefix, spec->prefix_len);
	spec->pad = '0';
	if (spec->width < spec->precision)
		spec->width = spec->precision;
	written += put_padding(spec);
	written += put_string(string, strlen);
	return (written);
}
