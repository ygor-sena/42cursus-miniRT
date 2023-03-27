/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:52:06 by yde-goes          #+#    #+#             */
/*   Updated: 2023/03/27 11:56:34 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRICES_H
# define MATRICES_H

# define MAX 4
# define SIZE 16

# include "libft.h"
# include "tuples.h"

typedef struct s_matrix
{
	float	matrix[MAX][MAX];
	size_t	size;
}	t_matrix;

typedef struct s_shearing
{
	float	p1;
	float	p2;	
}	t_shearing;

/* mx_operations.c */
t_matrix	multiply_matrix(t_matrix a, t_matrix b);
t_tuple		multiply_tuple_matrix(t_matrix a, t_tuple b);
t_matrix	transpose_matrix(t_matrix t);
t_matrix	inverted_matrix(t_matrix t);

/* mx_transformations.c */
t_matrix	translation(float x, float y, float z);
t_matrix	scaling(float x, float y, float z);
t_matrix	shearing(t_shearing x, t_shearing y, t_shearing z);

/* mx_rotations.c */
t_matrix	rotation_x(float rad);
t_matrix	rotation_y(float rad);
t_matrix	rotation_z(float rad);

/* mx_attributes.c */
float		get_determinant(t_matrix t);
t_matrix	get_submatrix(t_matrix t, size_t del_row, size_t del_col);
float		get_minor(t_matrix t, size_t row, size_t col);
float		get_cofactor(t_matrix t, size_t row, size_t col);
t_matrix	get_identity_matrix(void);

/* mx_utils.c */
t_shearing	to_shear(float a, float b);
t_matrix	create_matrix(const float table[MAX][MAX], size_t size);
int			compare_matrix(t_matrix	a, t_matrix b);
t_bool		is_invertible(t_matrix t);

#endif
