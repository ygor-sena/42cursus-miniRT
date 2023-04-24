/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:52:06 by yde-goes          #+#    #+#             */
/*   Updated: 2023/04/24 09:22:38 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRICES_H
# define MATRICES_H

# define MAX 4
# define SIZE 16

# include "libft.h"
# include "tuples.h"

/**
 * @brief The struct t_matrix stores a matrix up to 4x4 and size of 16. A matrix
 *        is a grid of numbers that can be manipulated as a single unit.
 *        Matrices and their operations are the foundational basis which will
 *        helps us to manipulate points, vectors and, ultimately, shapes.
 */
typedef struct s_matrix
{
	float	matrix[MAX][MAX];
	size_t	size;
}	t_matrix;

/**
 * @brief The struct t_shearing is a helper type to allow shearing operation on
 *        matrices. Shearing (or skew) is a complex operation where the 
 *        coordinate is changed in proportion to the other two coordinates. When
 *        doing it to a matrix, it means that x will change in proportion to y
 *        and z, y will change in proportion to x and z and, lastly, z will
 *        change in proportion to x and y. For example, to apply shearing to the
 *        x axis of a given matrix, we pass to shearing() a struct of type
 *        t_shearing containing the y and z values. For instance, when done to
 *        the y axis, we pass p1 and p2 which stands for x and z. Lastly, when
 *        applying it to the z axis, we pass x and y as p1 and p2, respectively.
 */
typedef struct s_shearing
{
	float	p1;
	float	p2;	
}	t_shearing;

/* ************************************************************************** */
/*                             MX_OPERATIONS.C                                */
/* ************************************************************************** */

/**
 * @brief This function multiplies two matrices. "Mx" means matrix. For more
 *        information about how matrix multiplication works, refer to the book
 *        TRTC on page 28.
 *
 * @param a Receives the first matrix to be multiplied.
 * @param b Receives the second matrix to be multiplied.
 * @return (t_matrix) Returns a new matrix which is the product of the two
 *         matrices passed to the function as parameter.
 */
t_matrix	multiply_mx_mx(t_matrix a, t_matrix b);

/**
 * @brief This function multiplies a matrix by a tuple. "Mx" means matrix and
 *        "tp" means tuple. For more information about how vector and matrix
 *        multiplication works, refer to the following link quoted by author
 *        J. Buck: https://betterexplained.com/articles/linear-algebra-guide/
 *
 * @param a Receives the matrix to be multiplied.
 * @param b Receives the tuple to be multiplied.
 * @return (t_tuple) Returns a new tuple which is the product of the two
 *         variables passed to the function as parameter.
 */
t_tuple		multiply_tp_mx(t_matrix a, t_tuple b);

/**
 * @brief This function transposes the matrix passed to the function as
 *        parameter. In other words, it turns the first row into the first
 *        column, the second row into the second column, and so forth. Thus,
 *        it's importante to remember that the transpose of the identity matrix
 *        always gives the own identity matrix as result.
 *
 * @param t Receives the matrix to be transposed.
 * @return (t_matrix) Returns a new matrix which is the transposition of the
 *         matrix passed to the function as parameter.
 */
t_matrix	transpose(t_matrix t);

/**
 * @brief This function get the inverse of a given matrix. That is, if you
 *        multiply some matrix A by another matrix B, producing C, you can
 *        multiply C by the inverse of B to get A again. To invert the matrix,
 *        this function employs a method known as cofactor expansion.
 *        Additionally, there some interesting properties of the inverse: 1)
 *        if you invert an identity matrix, the result is also an identity
 *        matrix. 2) when you multiply a matrix by its inverse, you get as
 *        result the identity matrix. 3) The inverse of the transpose of a
 *        matrix and the transpose of the inverse only commute if the matrix is
 *        symmetric or orthogonal. Otherwise, the result of the two operations
 *        will always be different.
 *
 * @param t Receives the matrix to be inverted.
 * @return (t_matrix) Returns a new matrix which is the inversion of the matrix
 *         passed to the function as parameter.
 */
t_matrix	inverse(t_matrix t);

/* ************************************************************************** */
/*                           MX_TRANSFORMATIONS.C                             */
/* ************************************************************************** */

/**
 * @brief This function translates a given matrix. Translation is a
 *        transformation that moves a point. Thus, it's important to note that
 *        the inverse of a translation matrix is another translation matrix that
 *        moves points in reverse.
 *
 * @param x Receives the x-axis value of the translation.
 * @param y Receives the y-axis value of the translation.
 * @param z Receives the z-axis value of the translation.
 * @return (t_matrix) Returns a new translated matrix from the coordinates
 *         passed to the function as parameter.
 */
t_matrix	translation(float x, float y, float z);

/**
 * @brief This function scales a given matrix by multiplication. When applied
 *        to an object centered at the origin, this transformation scales all
 *        points on the object, effectively making it larger (if the scale value
 *        is greater than 1) or smaller (if the scale value is less than 1).
 *        Note that reflection is scaling by a negative value.
 *
 * @param x Receives the x-axis value to scale.
 * @param y Receives the y-axis value to scale.
 * @param z Receives the z-axis value to scale.
 * @return (t_matrix) Returns a new scaled matrix from the coordinates passed to
 *         the function as parameter.
 */
t_matrix	scaling(float x, float y, float z);

/**
 * @brief This function applies shearing (or skew) transformation to a given
 *        matrix. It has the effect of making straight lines slanted. Each
 *        coordinate is changed in proportion to the other two coordinates. When
 *        doing it to a matrix, it means that x will change in proportion to y
 *        and z, y will change in proportion to x and z and, lastly, z will
 *        change in proportion to x and y.
 * 
 * @param x Receives a struct t_shearing storing the y and z values to change x
 *          in proportion to them. 
 * @param y Receives a struct t_shearing storing the x and z values to change y
 *          in proportion to them. 
 * @param z Receives a struct t_shearing storing the x and y values to change z
 *          in proportion to them. 
 * @return (t_matrix) Returns a new matrix after the shearing operation from
 *         values passed to the function as parameter.
 */
t_matrix	shearing(t_shearing x, t_shearing y, t_shearing z);

/* ************************************************************************** */
/*                             MX_ROTATIONS.C                                 */
/* ************************************************************************** */

/**
 * @brief This function rotates a given matrix around the x-axis.
 *
 * @param rad Receives the rotation around x axis to be performed in radians.
 * @return (t_matrix) Returns a new rotated matrix after the rotation passed to
 *         the function as parameter.
 */
t_matrix	rotation_x(float rad);

/**
 * @brief This function rotates a given matrix around the y-axis.
 *
 * @param rad Receives the rotation around y axis to be performed in radians.
 * @return (t_matrix) Returns a new rotated matrix after the rotation passed to
 *         the function as parameter.
 */
t_matrix	rotation_y(float rad);

/**
 * @brief This function rotates a given matrix around the z-axis.
 *
 * @param rad Receives the rotation around z axis to be performed in radians.
 * @return (t_matrix) Returns a new rotated matrix after the rotation passed to
 *         the function as parameter.
 */
t_matrix	rotation_z(float rad);

/* ************************************************************************** */
/*                             MX_ATTRIBUTES.C                                */
/* ************************************************************************** */

/**
 * @brief This function gets the determinant of a given matrix. The determinant
 *        is a number that is derived from the elements of a matrix. The name
 *        comes from the use of matrices to solve systems of equations, where
 *        it’s used to determine whether or not the system has a solution. If
 *        the determinant is zero, then the corresponding system of equations
 *        has no solution.
 *
 * @param t Receives the matrix to calculate its determinant.
 * @return (float) Returns a float value which is the determinant of the matrix
 *         passed to the function as parameter.
 */
float		get_determinant(t_matrix t);

/**
 * @brief This functions gets the submatrix of a given matrix. That is, what is
 *        left when you delete a single row and column from a matrix. The
 *        submatrix of a 4x4 matrix is 3x3 and the submatrix of a 3x3 matrix is
 *        2x2.
 *
 * @param t Receives the matrix from which the submatrix will be calculated.
 * @param del_row Receives a size_t value which stands for the row to be
 *                deleted when calculating the submatrix.
 * @param del_col Receives a size_t value which stands for the column to be
 *                deleted when calculating the submatrix.
 * @return (t_matrix) Returns the submatrix of the matrix passed to the function
 *         as parameter.
 */
t_matrix	get_submatrix(t_matrix t, size_t del_row, size_t del_col);

/**
 * @brief This function gets the minor of a given matrix. To put it differently,
 *        the minor of an element at row i and column j is the determinant of
 *        the submatrix at (i,j).
 *
 * @param t Receives the matrix from which the minor will be calculated.
 * @param row Receives the row value from which the minor will be calculated.
 * @param col Receives the column value from which the minor will be calculated.
 * @return (float) Returns the minor of the matrix passed to the function
 *         as parameter.
 */
float		get_minor(t_matrix t, size_t row, size_t col);

/**
 * @brief This function gets the cofactor of a given matrix. Cofactors are
 *        minors that have (possibly) had their sign changed. If row + column
 *        equals to an odd number as result, the minor must be negated.
 *        Therefore, if the row and column identifies a spot with a +, then the
 *        minor’s sign doesn’t change. If the row and column identifies a spot
 *        with a -, then the minor must be negated.
 *
 * @param t Receives the matrix from which the cofactor will be calculated.
 * @param row Receives the row value from which the cofactor will be calculated.
 * @param col Receives the column value from which the cofactor will be
 *            calculated.
 * @return (float) Returns the cofactor of the matrix passed to the function
 *         as parameter.
 */
float		get_cofactor(t_matrix t, size_t row, size_t col);

/**
 * @brief This fucntion gets a new matrix with the special attribute of being an
 *        identity matrix or multiplicative identity. That is, if you multiply
 *        any matrix or tuple by the identity matrix, you get back the matrix or
 *        tuple you started with.
 *
 * @return (t_matrix) Returns a new instance of an identity matrix.
 */
t_matrix	get_identity_matrix(void);

/* ************************************************************************** */
/*                                MX_UTILS.C                                  */
/* ************************************************************************** */

t_shearing	to_shear(float a, float b);

/**
 * @brief This function creates a matrix up to 4x4 and, therefore, size of 16
 *        (4x4). For instance, a matrix of 3x3 will have a size of 9(3x3).
 *
 * @param table A bidimensional array of const float containing the matrix.
 * @param size A size_t value containing how much elements the array has.
 * @return (t_matrix) Returns successfully a new matrix created with
 *         ft_memmove() from the array and array's size passed as parameter to
 *         the function.
 */
t_matrix	create_matrix(const float table[MAX][MAX], size_t size);

/**
 * @brief The function compare_matrix() checks if two matrices are identical or
 *        not. The matrices passed as parameter to the function are compared
 *        with ft_memcmp().
 *
 * @param a Receives the first matrix to be compared.
 * @param b Receives the second matrix to be compared.
 * @return (int) The function returns 0 if the matrices are identical.
 *         Otherwise, it returns a non-zero integer.
 */
int			compare_matrix(t_matrix	a, t_matrix b);

/**
 * @brief This function checks if a given matrix is invertible or not. Not every
 *        matrix is invertible. An matrix is invertible if its determinant is a
 *        non-zero number. If its determinant is 0, then the given matrix is not
 *        invertible.
 *
 * @param t Receives a matrix to be checked.
 * @return (t_bool) Returns TRUE if the given matrix is invertible. On the
 *         contrary, it returns FALSE if it's not invertible.
 */
t_bool		is_invertible(t_matrix t);

#endif
