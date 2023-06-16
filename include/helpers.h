/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:48:10 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/06/16 13:39:56 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// @file helpers.h
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

/* ************************************************************************** */
/*                                  FT_ATOF.C                                 */
/* ************************************************************************** */

/**
 * @brief Convert a string to a double.
 *
 * This function converts a string representation of a number to a double value.
 *
 * @param nptr The string to be converted.
 * @return The converted double value.
 */
double	ft_atof(const char *nptr);

#endif
