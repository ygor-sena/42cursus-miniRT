/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:48:10 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/20 20:56:26 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPERS_H
# define HELPERS_H

# include <stdio.h>
# include <stdlib.h>

/**
 * @brief Check if a pointer is null, and terminate the program if it is.
 *
 * This function is used to guard against out-of-memory errors, which can
 * cause memory allocation functions such as malloc() to return null pointers.
 *
 * @param ptr A pointer to check for nullness.
 * @return The same pointer as the input parameter.
 */
void	*oom(void *ptr);

#endif
