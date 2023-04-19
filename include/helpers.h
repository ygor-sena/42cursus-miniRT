/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:48:10 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/14 10:37:50 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPERS_H
# define HELPERS_H

# include <stdio.h>
# include <stdlib.h>

/* Out of memory guard. Check if ptr is null, if so, terminate the program. */
void	*oom(void *ptr);

#endif
