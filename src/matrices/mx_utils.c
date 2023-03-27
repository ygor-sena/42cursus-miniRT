/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:44:49 by yde-goes          #+#    #+#             */
/*   Updated: 2023/03/27 10:44:51 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrices.h"

/* UTILS OF TRANSFORMATIONS */
t_shearing	to_shear(float p1, float p2)
{
	return ((t_shearing){p1, p2});
}

/* WARNING: maybe use ft_zero to give null values if matrix is smaller */
t_matrix	create_matrix(const float table[MAX][MAX], size_t size)
{
	t_matrix	m;

	m.size = size;
	ft_memmove(m.matrix, table, sizeof(float) * SIZE);
	return (m);
}

/* Checks if the given matrices are equal */
int	compare_matrix(t_matrix a, t_matrix b)
{
	return (ft_memcmp(a.matrix, b.matrix, sizeof(float) * SIZE));
}

/* Checks if the given matrix is invertible */
t_bool	is_invertible(t_matrix t)
{
	if (get_determinant(t) == 0)
		return (FALSE);
	return (TRUE);
}
