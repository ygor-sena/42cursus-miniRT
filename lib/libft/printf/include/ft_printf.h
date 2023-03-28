/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 19:24:21 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/09/17 20:34:33 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include "libft.h"

typedef enum e_flags {
	LEFT,
	ZERO,
	PLUS,
	SPACE,
	HASH
}	t_flags;

typedef struct s_param {
	char		code;
	t_bool		flags[5];
	char		pad;
	int			width;
	int			precision;
	char		*prefix;
	int			prefix_len;
	const char	*init;
	const char	*end;
	const char	*next;
}	t_param;

int	ft_printf(const char *format, ...);

#endif
