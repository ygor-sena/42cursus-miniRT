/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 19:42:36 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/08/04 13:19:14 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include "../include/parser.h"
#include "../include/printer.h"

static int	ft_vprintf(const char *format, va_list args);

int	ft_printf(const char *format, ...)
{
	int		written;
	va_list	args;

	va_start(args, format);
	written = ft_vprintf(format, args);
	va_end(args);
	return (written);
}

static int	ft_vprintf(const char *format, va_list args)
{
	const char	*fmt;
	t_param		spec;
	int			written;

	init_parser();
	init_printer();
	fmt = find_spec(format);
	written = put_string(format, fmt - format);
	while (*fmt != '\0')
	{
		parse_spec(fmt, &spec);
		written += put_format(&spec, args);
		written += put_string(spec.end, (spec.next - spec.end));
		fmt = spec.next;
	}
	return (written);
}
