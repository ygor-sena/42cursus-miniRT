/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_attributes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:44:09 by yde-goes          #+#    #+#             */
/*   Updated: 2023/03/27 11:23:05 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrices.h"

/* Get the determinant of the given matrix */
/* float	get_determinant(t_matrix t)
{
	return ((t.matrix[0][0] * t.matrix[1][1]) \
		- (t.matrix[0][1] * t.matrix[1][0]));
} */
float	get_determinant(t_matrix t)
{
	size_t	col;
	float	det;

	det = 0;
	if (t.size == 2)
		det = (t.matrix[0][0] * t.matrix[1][1]) \
			- (t.matrix[0][1] * t.matrix[1][0]);
	else
	{
		col = -1;
		while (++col < t.size)
			det += (t.matrix[0][col] * get_cofactor(t, 0, col));
	}
	return (det);
}

/* Get the submatrix of the given matrix */
t_matrix	get_submatrix(t_matrix t, size_t del_row, size_t del_col)
{
	float	sub_m[MAX][MAX];
	size_t	row;
	size_t	col;

	row = -1;
	while (++row < t.size - 1)
	{
		col = -1;
		while (++col < t.size - 1)
			sub_m[row][col] = t.matrix \
				[row + (row >= del_row)][col + (col >= del_col)];
	}
	return (create_matrix(sub_m, t.size - 1));
}

/* float	get_minor(t_matrix t, size_t row, size_t col)
{
	return (get_determinant(get_submatrix(t, row, col)));
} */
/* Get the determinant of the submatrix of the given matrix */
float	get_minor(t_matrix t, size_t row, size_t col)
{
	t_matrix	m;
	float		minor;

	m = get_submatrix(t, row, col);
	minor = get_determinant(m);
	return (minor);
}

float	get_cofactor(t_matrix t, size_t row, size_t col)
{
	float		cofactor;

	cofactor = get_minor(t, row, col);
	if ((row + col) % 2 == 1)
		cofactor *= -1;
	return (cofactor);
}

t_matrix	get_identity_matrix(void)
{
	const float	table_id[MAX][MAX] = {
	{1, 0, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1},
	};

	return (create_matrix(table_id, MAX));
}
