/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:48:10 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/26 09:07:52 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPERS_H
# define HELPERS_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>

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
 * @return Returns the pointer if malloc() succeeded. Otherwise, the program is
 *         ceased.
 */
void	*oom(void *ptr);

/* ************************************************************************** */
/*                                   SWAP.C                                   */
/* ************************************************************************** */

/**
 * @brief This function swaps numbers' position if the first parameter is bigger
 *        than the second parameter.
 * 
 * @param nbr1 Receives the first number to be compared.
 * @param nbr2 Receives the second the number to be compared.
 */
void	swap(double *nbr1, double *nbr2);

#endif
