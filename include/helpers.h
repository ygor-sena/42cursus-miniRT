/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:48:10 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/04/24 09:25:30 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPERS_H
# define HELPERS_H

# include <stdio.h>
# include <stdlib.h>

/**
 * ABOUT THE HEADER HELPERS.H
 *
 * This header contains auxiliary functions for the program as a whole, i.e.,
 * functions that aren't subfunctions of a specific task in a given module.
 */

/* ************************************************************************** */
/*                                  GUARDS.C                                  */
/* ************************************************************************** */

/**
 * @brief oom() means outside memory guard. This function checks if the pointer
 *        passed as parameter is NULL. If true, a message with the corresponding
 *        errno number is printed and the program is terminated.
 *
 * @param ptr The pointer to be checked after calling malloc().
 * @return (void *) Returns the pointer if malloc() succeeded. Otherwise, the
 *         program is ceased.
 */
void	*oom(void *ptr);

#endif
