/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:11:15 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/23 13:58:59 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H

# include <fcntl.h>
# include <stdlib.h>
# include <string.h>

# include "world.h"
# include "canvas.h"

# define ERROR_UNEXPECTED_ELEMENT "Unexpected element"
# define ERROR_EXPECTED_NUMBER "Expected a number"
# define ERROR_EXPECTED_NEWLINE "Expected newline"
# define ERROR_EXPECTED_COMMA "Expected a comma"

# define INVALID_NUMBER "Invalid number"
# define INVALID_VECTOR "Vector components must be between -1 and 1.\n"
# define INVALID_COLOR "Color values must be between 0 and 255.\n"
# define INVALID_LIGHT "Light ratio must be between 0 and 1.\n"
# define INVALID_FOV "Field of view must be between 0 and 180.\n"
# define INVALID_DIMENSION "Dimensions should be positive.\n"

# define ERROR_CAMERA "Only one camera allowed.\n"
# define ERROR_AMBIENT "Only one ambient light allowed.\n"

typedef enum e_token
{
	TOKEN_AMBIENT_LIGHT,
	TOKEN_CAMERA,
	TOKEN_LIGHT,
	TOKEN_SPHERE,
	TOKEN_PLANE,
	TOKEN_CYLINDER,
	TOKEN_NEWLINE,
	TOKEN_COMMENT,
	TOKEN_ERROR,
	TOKEN_COUNT
}	t_token;

/**
 * @brief Represents a scanner.
 *
 * The scanner structure is used for scanning and tokenizing input text.
 *
 * The scanning process is performed using two pointers, `consume` and
 * `current`, which need to be kept separate. While `current` reads from the
 * input and checks if the character sequence is correct, `consume` remains
 * pointing to the beginning of the portion being verified. This eliminates
 * the need to split the input into pieces and allows for precise identification
 * of the section of input that needs to be converted.
 *
 * @param line Stores the line number being read.
 * @param start A pointer to the first character of the line.
 * @param consume A pointer passed to the number conversion functions.
 * @param current A pointer used for reading character by character.
 * @param message A pointer to the current error message, if any.
 */
typedef struct s_scanner
{
	int			line;
	const char	*start;
	const char	*consume;
	const char	*current;
	const char	*message;
}	t_scanner;

////////////////////////////////////////////////////////////////////////////////
/// Scanner

/**
 * @brief Initializes a scanner with the provided source.
 *
 * This function initializes a scanner structure with the given source.
 *
 * @param scanner A pointer to the scanner structure to be initialized.
 * @param source  The source to be scanned and tokenized.
 */
void		init_scanner(t_scanner *scanner, const char *source);

/* Identify whether the character sequence in the input forms an integer. */
t_bool		scan_integer(t_scanner *scanner);

/* Identify whether the character sequence in the input forms an float. */
t_bool		scan_float(t_scanner *scanner);

/* Verify if there is a comma in the input. */
t_bool		scan_comma(t_scanner *scanner);

/* Verify if there is a newline in the input. */
t_bool		scan_newline(t_scanner *scanner);

////////////////////////////////////////////////////////////////////////////////
// Parse types
t_token		parse_type(t_scanner *scanner);

////////////////////////////////////////////////////////////////////////////////
/// Scanner utils

/* Advance the `current` pointer to the next character. */
void		advance(t_scanner *scanner);

/* Skip all whitespace characters encountered. */
void		skip_whitespace(t_scanner *scanner);

/* Check if it is a sign. */
int			is_sign(int c);

////////////////////////////////////////////////////////////////////////////////
/// Parse

/* Open and read a file, assigning each found element to the scene. */
t_bool		parse(char *filename, t_scene *scene);

////////////////////////////////////////////////////////////////////////////////
/// Parse element

/**
 * @brief Parses and processes an element from the input.
 *
 * This function parses an element from the input and performs the necessary
 * processing based on the element's type. It updates the scene with the parsed
 * element and returns the result indicating the success or failure of the parse.
 *
 * @param scanner A pointer to the scanner structure.
 * @param scene   A pointer to the scene structure.
 * @return        A boolean value indicating whether the parse was successful.
 */
t_bool		parse_element(t_scanner *scanner, t_scene *scene, int totals[]);

/* Parse comments. */
t_bool		parse_comment(t_scanner *scanner);

/* Add objects to the world. */
void		add_object_to_world(t_shape *shape, t_world *world);

/* Add lights to the world. */
void		add_light_to_world(t_light *light, t_world *world);

////////////////////////////////////////////////////////////////////////////////
/// Parse basic

/* Convert a float from the input and store it in `result`. */
t_bool		parse_float(t_scanner *scanner, float *result);

/* Convert the light ratio from the input and store it in `light`. */
t_bool		parse_light_ratio(t_scanner *scanner, float *light);

/* Convert the field of view from the input and store it in `fov`. */
t_bool		parse_field_of_view(t_scanner *scanner, int *fov);

/* Convert the dimension from the input and store it in `dimension`. */
t_bool		parse_dimension(t_scanner *scanner, float *dimension);

////////////////////////////////////////////////////////////////////////////////
/// Parse grouped

/* Convert a color from the input and store it in `result`. */
t_bool		parse_color(t_scanner *scanner, t_color *result);

/* Convert a position from the input and store it in `position`. */
t_bool		parse_position(t_scanner *scanner, t_point *position);

/* Convert a direction from the input and store it in `direction`. */
t_bool		parse_direction(t_scanner *scanner, t_vector *direction);

////////////////////////////////////////////////////////////////////////////////
/// Parse ambient

/* Convert the ambient light from the input and add it to the scene. */
t_bool		parse_ambient_light(t_scanner *scanner, t_scene *scene);

/* Convert the camera from the input and add it to the scene. */
t_bool		parse_camera(t_scanner *scanner, t_scene *scene);

/* Convert the light point from the input and add it to the scene. */
t_bool		parse_light(t_scanner *scanner, t_scene *scene);

////////////////////////////////////////////////////////////////////////////////
/// Parse shapes

/* Convert a sphere from the input and add it to the scene. */
t_bool		parse_sphere(t_scanner *scanner, t_scene *scene);

/* Convert a plane from the input and add it to the scene. */
t_bool		parse_plane(t_scanner *scanner, t_scene *scene);

/* Convert a cylinder from the input and add it to the scene. */
t_bool		parse_cylinder(t_scanner *scanner, t_scene *scene);

////////////////////////////////////////////////////////////////////////////////
/// Parse utils

/* Display an error message based on the state of the scanner. */
t_bool		report_error(t_scanner *scanner);

/* Validate if a number is within a certain range. */
t_bool		validate_range(float value, float start, float end);

/* Get the column where an error occurred. */
int			get_error_column(t_scanner *scanner);

/* Determine the error message based on the state of the scanner. */
void		set_error_state(t_scanner *scanner, const char *error_message);

////////////////////////////////////////////////////////////////////////////////
/// Helpers

/* Convert a string to a float. */
double		ft_atof(const char *nptr);

#endif // !PARSER_H
