/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 10:28:36 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/08/05 13:42:04 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/printer.h"

t_out	*conversion_array(void)
{
	static t_out	array[128];

	return (array);
}

void	init_printer(void)
{
	t_out	*types;

	types = conversion_array();
	types['c'] = out_char;
	types['s'] = out_string;
	types['p'] = out_pointer;
	types['d'] = out_signed;
	types['i'] = out_signed;
	types['u'] = out_unsigned;
	types['x'] = out_unsigned;
	types['o'] = out_unsigned;
	types['b'] = out_unsigned;
	types['X'] = out_unsigned;
	types['%'] = out_percent;
}
