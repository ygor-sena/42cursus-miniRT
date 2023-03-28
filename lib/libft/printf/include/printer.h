/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 17:22:09 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/09/17 20:54:11 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTER_H
# define PRINTER_H

# include "ft_printf.h"

typedef int	(*t_out)(t_param *, va_list);

t_out	*conversion_array(void);
void	init_printer(void);

int		out_char(t_param *spec, va_list args);
int		out_string(t_param *spec, va_list args);
int		out_pointer(t_param *spec, va_list args);
int		out_signed(t_param *spec, va_list args);
int		out_unsigned(t_param *spec, va_list args);
int		out_percent(t_param *spec, va_list args);

int		put_format(t_param *spec, va_list args);
int		put_padding(t_param *spec);
int		put_string(const char *string, int length);
int		put_number_justified(t_param *spec, char *string, int strlen);
void	set_number_precision(t_param *spec, int strlen);
char	*ft_itoa_base(unsigned long nbr, char *nbr_sys);

#endif
