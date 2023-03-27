/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_operations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:44:17 by yde-goes          #+#    #+#             */
/*   Updated: 2023/03/27 11:56:08 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrices.h"
#include "tuples.h"

/*	WARNING: Maybe refactor 4x4 multiplication, 
*	same case of the function below
*/
t_matrix	multiply_matrix(t_matrix a, t_matrix b)
{
	float		m[MAX][MAX];
	size_t		row;
	size_t		col;

	ft_bzero(m, sizeof(float) * SIZE);
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
t_tuple	multiply_tuple_matrix(t_matrix a, t_tuple b)
{
	float		t[MAX];
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
*	ft_bzero(m, sizeof(float) * SIZE); line 70
*/
t_matrix	transpose_matrix(t_matrix	t)
{
	size_t		row;
	size_t		col;
	float		m[MAX][MAX];

	row = -1;
	while (++row < t.size)
	{
		col = -1;
		while (++col < t.size)
			m[col][row] = t.matrix[row][col];
	}
	return (create_matrix(m, t.size));
}

/* float newPrecision(float n, float i)
{
    return floor(pow(10,i)*n)/pow(10,i);
} 
*/
/*	This function can be refactored because of decimal precision
*	Is five precision points suficient? Ow do we need 9?
	ft_bzero(inverted, sizeof(float) * SIZE); line 99
 */
t_matrix	inverted_matrix(t_matrix t)
{	
	float	inverted[MAX][MAX];
	float	determinant;	
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
