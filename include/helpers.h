/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:48:10 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/17 17:30:10 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPERS_H
# define HELPERS_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# include "libft.h"

// WARNING: this file should have only one header "miniRT.h" with EPSILON def

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

/**
 * @brief This function checks if the two numbers are approximately zero when
 *        subtracted. The reference is EPSILON, which is equal to 0.00001.
 * 
 * @param a Receives the first float number to be subtracted.
 * @param b receives the second float number to be subtracted.
 * @return The function returns TRUE if the numbers are approximately equal to
 *         zero within EPSILON range. Otherwise, it returns FALSE.
 */
t_bool	is_epsilon_zero(float a, float b);

/**
 * @brief This function swaps numbers' position if the first parameter is bigger
 *        than the second parameter.
 * 
 * @param t1 Receives the first number to be compared.
 * @param t2 Receives the second the number to be compared.
 */
void	swap(float *t1, float *t2);

#endif
