/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_attributes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:44:09 by yde-goes          #+#    #+#             */
/*   Updated: 2023/05/30 13:26:53 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrices.h"

double	get_determinant(t_matrix t)
{
	size_t	col;
	double	det;

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

t_matrix	get_submatrix(t_matrix t, size_t del_row, size_t del_col)
{
	double	sub_m[MAX][MAX];
	size_t	row;
	size_t	col;

	row = -1;
	if (t.size == 0)
		return (get_identity_matrix());
	while (++row < t.size - 1)
	{
		col = -1;
		while (++col < t.size - 1)
			sub_m[row][col] = t.matrix \
				[row + (row >= del_row)][col + (col >= del_col)];
	}
	return (create_matrix(sub_m, t.size - 1));
}

double	get_minor(t_matrix t, size_t row, size_t col)
{
	t_matrix	m;
	double		minor;

	m = get_submatrix(t, row, col);
	minor = get_determinant(m);
	return (minor);
}

double	get_cofactor(t_matrix t, size_t row, size_t col)
{
	double		cofactor;

	cofactor = get_minor(t, row, col);
	if ((row + col) % 2 == 1)
		cofactor *= -1;
	return (cofactor);
}

t_matrix	get_identity_matrix(void)
{
	const double	table_id[MAX][MAX] = {
	{1, 0, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1},
	};

	return (create_matrix(table_id, MAX));
}
