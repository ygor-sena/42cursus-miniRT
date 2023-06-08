/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:21:56 by yde-goes          #+#    #+#             */
/*   Updated: 2023/06/08 18:51:06 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATTERNS_H
# define PATTERNS_H

# include "matrices.h"

typedef struct s_pattern	t_pattern;
typedef struct s_checker	t_checker;

/**
 * @brief t_pttr_at is a function-type that receives the function's name of a
 *        pattern to be applied. For example, to apply a checkered pattern, the
 *        t_pttr_at is "checkered_at", which is the function that computes a
 *        checkered pattern on a given shape. To apply a striped pattern, use
 *        stripe_at instead.
 */
typedef t_color				(*t_pttr_at)(t_pattern pattern,
												t_point world_point);
typedef t_checker			(*t_uv_map)(t_point point);

/**
 * @brief This structure encapsulates the function uv_checkers().
 *
 * @param width Describes how many squares the pattern creates in u, that is,
 *        in the vertical axis.
 * @param height Describes how many squares the pattern creates in v, that is,
 *        in the horizontal axis.
 * @param color_a Describes the first color of the square to be applied.
 * @param color_a Describes the second color of the square to be applied.
 */
typedef struct s_checker
{
	double	width;
	double	height;
	t_color	color_a;
	t_color	color_b;
}	t_checker;

/**
 * @brief This structure creates a t_pattern subclass (the same as t_pttr_at,
 *        which calls stripe_at() or checkered_at()). t_text_map is a subclass
 *        that uses spherical_map(), planar_map() or cylindrical_map() to define
 *        how to apply a pattern on a given 2D or 3D shape's surface.
 *
 * @param uv_pattern Contains information about the pattern to applied on a
 *                   given shape's surface.
 * @param uv_map Contains the corresponding shape's function that will correctly
 *               apply the texture on its surface. For example, if the shape is
 *               a plane, this field must be planar_map. If it's a cylinder, it
 *               must be cylindrical_map and if it's a sphere, it must be
 *               spherical_map.
 */
typedef struct s_text_map
{
	t_checker	uv_pattern;
	t_uv_map	uv_map;
}	t_text_map;

/**
 * @brief The struct of type t_uv_image represents an image used for texturing
 *        another image.
 *
 * The t_uv_image structure contains the necessary fields for storing image data
 * and relevant information used for texturing operations. It is used to define
 * an image that can be applied as a texture on another image or rendered onto
 * a canvas.
 *
 * @param mlx_ptr A pointer to a connection with the Xserver.
 * @param win_ptr A pointer to a window created with MLX (MinilibX).
 * @param img_ptr A pointer to an image created with MLX (MinilibX).
 * @param addr    A pointer to the image data, indicating how to write data on
 *                pixels of the image.
 * @param bpp     The bits per pixel value of the image.
 * @param line_len The line length value of the image.
 * @param endian   The endianness order of the image.
 * @param width    The width of the image in pixels.
 * @param height   The height of the image in pixels.
 */
typedef struct s_uv_image
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_uv_image;

/**
 * @brief The type t_pattern contatins all the necessary information to apply a
 *        texture on a given shape's surface.
 * @param has_pattern Stores TRUE if shape has a pattern or FALSE, if not.
 * @param pattern_at Receives a pattern function to apply the corresponding
 *                   pattern. For more information, see t_pttr_at description.
 * @param texture_map This structure creates a t_pattern subclass (the same as
 *                    t_pttr_at, which calls stripe_at() or checkered_at()).
 *                    t_text_map is a subclass that uses spherical_map(),
 *                    planar_map() or cylindrical_map() to define how to apply a
 *                    pattern on a given 2D or 3D shape's surface.
 * @param width Receives u, the horizontal value of checkers squares.
 * @param height Receives v, the vertical value of checkers squares.
 * @param a Receives the first color of a given pattern to be applied.
 * @param b Receives the second color of a given pattern to be applied.
 * @param transform Stores matrix transformation so that pattern be manipulated.
 */
typedef struct s_pattern
{
	t_bool		has_pattern;
	t_pttr_at	pattern_at;
	t_text_map	texture_map;
	t_color		a;
	t_color		b;
	t_matrix	transform;
	t_matrix	inverse;
	t_matrix	transpose;
	t_uv_image	canvas;
}	t_pattern;

/* ************************************************************************** */
/*                               PATTERNS.C                                   */
/* ************************************************************************** */

/**
 * @brief This function creates a new default pattern with the following
 *        properties: it has a stripe pattern and it receives the color passed
 *        as parameter to the function.
 *
 * @param a Receives the first color of a given pattern to be applied.
 * @param b Receives the second color of a given pattern to be applied.
 * @return This function successfully returns a new pattern structure.
 */
t_pattern	new_pattern(t_color a, t_color b);

/**
 * @brief This function applies a stripe pattern on shape's surface located at
 *        a given world point. It checks which pattern color should or not be
 *        applied at a specific point of the world.
 *
 * @param pattern Stores the pattern to be applied.
 * @param world_point Contains the world's point to be evaluated.
 * @return The function returns the first pattern color a if condition is met.
 *         Otherwise, it returns the second pattern b.
 */
t_color		stripe_at(t_pattern pattern, t_point world_point);

/**
 * @brief This function applies a checkered pattern on shape's surface located
 *        at a given world point. It checks which pattern color should or not be
 *        applied at a specific point of the world.
 *
 * @param pattern Stores the pattern to be applied.
 * @param world_point Contains the world's point to be evaluated.
 * @return The function returns the first pattern color a if condition is met.
 *         Otherwise, it returns the second pattern b.
 */
t_color		checkered_at(t_pattern pattern, t_point world_point);

/**
 * @brief Calculates the color of a bumped pattern applied to a shape's surface
 *        at a given point.
 *
 * A bumped pattern is a pattern that adds a sense of depth or texture to a
 * surface.
 * This function applies a bumped pattern on the surface of a shape at the
 * specified point. It determines the color of the pattern at that point based
 * on the pattern and the position of the point.
 *
 * @param pattern A structure of type t_pattern that stores the bumped pattern
 *                to be applied.
 * @param point A structure of type t_point representing the point on the
 *              shape's surface.
 * @return The color of the pattern at the given point.
 */
t_color		bumped_at(t_pattern pattern, t_point point);

/**
 * @brief This function assigns a transformation matrix to a pattern, which is
 *        used to manipulate the way the pattern is rendered.
 *
 * @param pattern Receives the pattern structure to alter transform's field.
 * @param transform Receives the matrix transformation to be assigned.
 */
void		set_pattern_transform(t_pattern *pattern, t_matrix transform);

/* ************************************************************************** */
/*                               CHECKERS.C                                   */
/* ************************************************************************** */

/**
 * @brief This function creates a checker structure to be used by pattern
 *        functions.
 *
 * @param width Describes how many squares the pattern creates in u, that is,
 *        in the vertical axis.
 * @param height Describes how many squares the pattern creates in v, that is,
 *        in the horizontal axis.
 * @param a Describes the first color of the square to be applied.
 * @param b Describes the second color of the square to be applied.
 * @return Returns a data structure of type t_cheker that encapsulates the
 *         function's parameters.
 */
t_checker	uv_checkers(double width, double height, t_color a, t_color b);

/**
 * @brief This function gets the pattern's color and at the given width (v) and
 *        height (v) coordinates stored at the structure t_checker.
 * 
 * @param checkers Contains the how many squares in x and y axes there are and
 *                 which colors are to be applied on a surface.
 * @param u This parameter specifies the x location.
 * @param v This parameter specifies the y location.
 * @return Returns the pattern's color at the given u and v coordinates, where
 *         both u and v are floating point numbers between 0 and 1, inclusive.
 */
t_color		uv_pattern_at(t_checker checkers, double u, double v);

/* ************************************************************************** */
/*                               MAPPINGS.C                                   */
/* ************************************************************************** */

/**
 * @brief This function saves t_checker struct to t_pattern struct. It sends
 *        information to t_pattern about how to apply a given pattern (uv_map)
 *        and what is the pattern to be applied (checkers).
 *
 * @param pattern Stores the pattern to be applied.
 * @param checkers Contains the how many squares in x and y axes there are and
 *                 which colors are to be applied on a surface.
 * @param uv_map Contains the corresponding shape's function that will correctly
 *               apply the texture on its surface. For example, if the shape is
 *               a plane, this field must be planar_map. If it's a cylinder, it
 *               must be cylindrical_map and if it's a sphere, it must be
 *               spherical_map.
 */
void		texture_map(t_pattern *pattern,
				t_checker checkers, t_uv_map uv_map);

/**
 * @brief This function renders a 3D point of a sphere on its surface to a 2D
 *        point (u, v) on the flattered surface.
 *
 * @param point Specifies the point to be converted.
 * @return Returns the (u, v) pair corresponding to the given 3D point p.
 */
t_checker	spherical_map(t_point point);

/**
 * @brief This function renders a 3D point of a cylinder on its surface to a 2D
 *        point (u, v) on the flattered surface.
 *
 * @param point Specifies the point to be converted.
 * @return Returns the (u, v) pair corresponding to the given 3D point p.
 */
t_checker	cylindrical_map(t_point point);

/**
 * @brief This function renders a 3D point of a plane on its surface to a 2D
 *        point (u, v) on the flattered surface.
 *
 * @param point Specifies the point to be converted.
 * @return Returns the (u, v) pair corresponding to the given 3D point p.
 */
t_checker	planar_map(t_point point);

#endif
