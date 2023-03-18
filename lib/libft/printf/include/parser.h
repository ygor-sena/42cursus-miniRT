/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 21:35:18 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/10/18 21:01:10 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "ft_printf.h"

typedef void	(*t_flag)(t_param *);

t_flag		*flag_array(void);
void		init_parser(void);
void		clean_info(t_param *spec);
int			read_nbr(const char **format);

void		flag_left(t_param *spec);
void		flag_showsign(t_param *spec);
void		flag_space(t_param *spec);
void		flag_hash(t_param *spec);
void		flag_padding(t_param *spec);

void		parse_spec(const char *format, t_param *spec);
const char	*find_spec(const char *format);

#endif
