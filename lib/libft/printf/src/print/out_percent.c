/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_percent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 10:29:41 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/08/05 12:27:08 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/printer.h"

int	out_percent(t_param *spec, va_list args)
{
	(void) args;
	return (put_string(&spec->code, 1));
}
