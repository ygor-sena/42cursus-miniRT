/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_pointer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 14:01:40 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/08/11 22:26:21 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/printer.h"

static int	print_nil(t_param *spec);

int	out_pointer(t_param *spec, va_list args)
{
	unsigned long	nbr;
	char			*string;
	int				written;
	int				strlen;

	written = 0;
	nbr = va_arg(args, unsigned long);
	if (nbr == 0)
		return (print_nil(spec));
	string = ft_itoa_base(nbr, LOWER_HEX);
	strlen = ft_strlen(string);
	set_number_precision(spec, strlen);
	spec->prefix = "0x";
	spec->prefix_len = 2;
	written = put_number_justified(spec, string, strlen);
	free(string);
	return (written);
}

static int	print_nil(t_param *spec)
{
	spec->width--;
	return (put_number_justified(spec, "(nil)", 5));
}
