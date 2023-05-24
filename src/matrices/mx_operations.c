/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_operations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:44:17 by yde-goes          #+#    #+#             */
/*   Updated: 2023/05/24 11:13:37 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrices.h"
#include "tuples.h"

/*	WARNING: Maybe refactor 4x4 multiplication, 
*	same case of the function below
*/
t_matrix	multiply_mx_mx(t_matrix a, t_matrix b)
{
	double		m[MAX][MAX];
	size_t		row;
	size_t		col;

	ft_bzero(m, sizeof(double) * SIZE);
	row = -1;
	while (++row < MAX)
	{
		col = -1;
		while (++col < MAX)
		{
			m[row][col] = a.matrix[row][0] * b.matrix[0][col]
				+ a.matrix[row][1] * b.matrix[1][col]
				+ a.matrix[row][2] * b.matrix[2][col]
				+ a.matrix[row][3] * b.matrix[3][col];
		}
	}
	return (create_matrix(m, MAX));
}

/*	WARNING: Maybe this one will need refactor.
*	MAX --> t.size
*	aux variable to multiply row/columns
*/
t_tuple	multiply_tp_mx(t_matrix a, t_tuple b)
{
	double		t[MAX];
	size_t		row;

	row = -1;
	while (++row < MAX)
	{
		t[row] = a.matrix[row][0] * b.x \
			+ a.matrix[row][1] * b.y \
			+ a.matrix[row][2] * b.z \
			+ a.matrix[row][3] * b.w;
	}
	return (tuple(t[0], t[1], t[2], t[3]));
}

/* 
*	OBS: assuming that t will always be a 4x4 matrix.
*	If it's a 3x3 or 2x2, maybe it'll generate a bug...
*	ft_bzero(m, sizeof(double) * SIZE); line 70
*/
t_matrix	transpose(t_matrix	t)
{
	size_t		row;
	size_t		col;
	double		m[MAX][MAX];

	row = -1;
	while (++row < t.size)
	{
		col = -1;
		while (++col < t.size)
			m[col][row] = t.matrix[row][col];
	}
	return (create_matrix(m, t.size));
}

/* double newPrecision(double n, double i)
{
    return floor(pow(10,i)*n)/pow(10,i);
} 
*/
/*	This function can be refactored because of decimal precision
*	Is five precision points suficient? Ow do we need 9?
	ft_bzero(inverted, sizeof(double) * SIZE); line 99
 */
t_matrix	inverse(t_matrix t)
{	
	double	inverted[MAX][MAX];
	double	determinant;	
	size_t	row;
	size_t	col;

	if (!is_invertible(t))
		return (get_identity_matrix());
	determinant = get_determinant(t);
	row = -1;
	while (++row < t.size)
	{
		col = -1;
		while (++col < t.size)
			inverted[col][row] = \
				get_cofactor(t, row, col) / determinant;
	}
	return (create_matrix(inverted, MAX));
}
