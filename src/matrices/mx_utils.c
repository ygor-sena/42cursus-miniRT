/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:44:49 by yde-goes          #+#    #+#             */
/*   Updated: 2023/05/24 11:13:56 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrices.h"

/* UTILS OF TRANSFORMATIONS */
t_shearing	to_shear(double p1, double p2)
{
	return ((t_shearing){p1, p2});
}

/* WARNING: maybe use ft_zero to give null values if matrix is smaller */
t_matrix	create_matrix(const double table[MAX][MAX], size_t size)
{
	t_matrix	m;

	m.size = size;
	ft_memmove(m.matrix, table, sizeof(double) * SIZE);
	return (m);
}

/* Checks if the given matrices are equal */
int	compare_matrix(t_matrix a, t_matrix b)
{
	return (ft_memcmp(a.matrix, b.matrix, sizeof(double) * SIZE));
}

/* Checks if the given matrix is invertible */
t_bool	is_invertible(t_matrix t)
{
	if (get_determinant(t) == 0)
		return (FALSE);
	return (TRUE);
}
