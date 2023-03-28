/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_signed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 14:01:35 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/08/05 12:27:14 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/printer.h"

static void	set_signed_prefix(t_param *spec, long *nbr);

int	out_signed(t_param *spec, va_list args)
{
	long	nbr;
	char	*string;
	int		written;
	int		strlen;

	written = 0;
	nbr = va_arg(args, int);
	set_signed_prefix(spec, &nbr);
	string = ft_itoa_base(nbr, DECIMAL);
	if (nbr == 0 && spec->precision == 0)
		string[0] = 0;
	strlen = ft_strlen(string);
	set_number_precision(spec, strlen);
	written = put_number_justified(spec, string, strlen);
	free(string);
	return (written);
}

static void	set_signed_prefix(t_param *spec, long *nbr)
{
	if (*nbr < 0)
	{
		spec->prefix = "-";
		spec->prefix_len = 1;
		*nbr *= (-1);
	}
	else if (spec->flags[PLUS])
	{
		spec->prefix = "+";
		spec->prefix_len = 1;
	}
	else if (spec->flags[SPACE])
	{
		spec->prefix = " ";
		spec->prefix_len = 1;
	}
}
