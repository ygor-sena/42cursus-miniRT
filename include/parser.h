/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:11:15 by mdias-ma          #+#    #+#             */
/*   Updated: 2024/04/04 09:50:05 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// @file parser.h
#ifndef PARSER_H
# define PARSER_H

# include <fcntl.h>
# include <stdlib.h>
# include <string.h>

# include "world.h"
# include "canvas.h"

# define BUFFER 1024

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
# define INVALID_FILE "Invalid texture file"
# define NON_NORMALIZED "Vector should be normalized"

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
	TOKEN_CONE,
	TOKEN_NEWLINE,
	TOKEN_COMMENT,
	TOKEN_ERROR,
	TOKEN_COUNT
}	t_token;

/**
 * @brief Stores the parameters of the shapes cone and cylinder from configuration
 * file after they have been verified by the scanner. 
 *
 * @param origin Stores the origin of the cone or cylinder.
 * @param direction Stores the direction of the cone or cylinder.
 * @param diameter Stores the diameter of the cone or cylinder.
 * @param height Stores the height of the cone or cylinder.
 * @param radius Stores the radius of the cone or cylinder.
 * @param minimum Stores the cone or cylinder minimum height, i.e, lowest height.
 * @param maximum Stores the cone or cylinder maxinum height, i.e, highest height.
 */
typedef struct s_param
{
	t_point		origin;
	t_vector	direction;
	double		diameter;
	double		height;
	float		radius;
	float		minimum;
	float		maximum;
}	t_param;

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
	const char	*sync;
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

/**
 * @brief Identify if input character sequence forms an integer.
 *
 * This function determines whether the character sequence in the input
 * forms a valid integer.
 *
 * @param scanner Pointer to the scanner.
 * @return        True if the sequence is a valid integer, false otherwise.
 */
t_bool		scan_integer(t_scanner *scanner);

/**
 * @brief Identify if input character sequence forms a double number.
 *
 * This function checks if the character sequence in the input scanner
 * represents a valid double number.
 *
 * @param scanner Pointer to the scanner.
 * @return        True if the sequence is a valid double, false otherwise.
 */
t_bool		scan_double(t_scanner *scanner);

/**
 * @brief Verify presence of a comma in the input.
 *
 * This function verifies if there is a comma character in the input scanner.
 *
 * @param scanner Pointer to the scanner.
 * @return        True if a comma is present, false otherwise.
 */
t_bool		scan_comma(t_scanner *scanner);

/**
 * @brief Verify presence of a newline in the input.
 *
 * This function verifies if there is a newline character in the given scanner.
 *
 * @param scanner Pointer to the scanner.
 * @return        True if a newline is present, false otherwise.
 */
t_bool		scan_newline(t_scanner *scanner);

////////////////////////////////////////////////////////////////////////////////
/// Parse types

/**
 * @brief Identify token characterizing analysis type in a line.
 *
 * Determines the token representing the analysis type in a line of the input.
 *
 * @param scanner Pointer to scanner object.
 * @return        Token representing the analysis type.
 */
t_token		parse_type(t_scanner *scanner);

////////////////////////////////////////////////////////////////////////////////
/// Scanner utils

/**
 * @brief Advance the `current` pointer to the next character.
 *
 * This function advances the current pointer of the scanner
 * to the next character in the input.
 *
 * @param scanner Pointer to the scanner.
 */
void		advance(t_scanner *scanner);

/**
 * @brief Skip all encountered whitespace characters.
 *
 * This function skips all whitespace characters encountered by advancing
 * the current pointer of the scanner past them in the input.
 *
 * @param scanner Pointer to the scanner.
 */
void		skip_whitespace(t_scanner *scanner);

/**
 * @brief Check if character is a sign.
 *
 * Checks if given character represents a sign (positive or negative).
 *
 * @param c Character to be checked.
 * @return  1 if sign, 0 otherwise.
 */
int			is_sign(int c);

/**
 * @brief Saves the current position of the scanner for later restoration and
 * synchronization with the parser.
 *
 * This function takes a pointer to a scanner object and saves the current
 * position of the scanner in the sync pointer of the scanner object.
 * The saved position can be used later to restore the scanner to its current
 * position and synchronize it with the parser.
 *
 * @param scanner A pointer to a scanner object.
 */
void		save_position(t_scanner *scanner);

/**
 * @brief Synchronizes the scanner with the parser by restoring its position
 * to a previously saved position.
 *
 * This function takes a pointer to a scanner object and restores the scanner
 * to the saved position in the sync pointer of the scanner object,
 * synchronizing it with the parser.
 *
 * @param scanner A pointer to a scanner object.
 */
void		sync_position(t_scanner *scanner);

////////////////////////////////////////////////////////////////////////////////
/// Parse

/**
 * @brief Open and read a file, assigning found elements to the scene.
 *
 * This function opens and reads a file specified by the filename. It parses
 * the content of the file, assigning each found element to the given scene.
 *
 * @param  filename Name of the file to open and read.
 * @param  scene Pointer to the scene object.
 * @return True if successful, false otherwise.
 */
t_bool		parse(char *filename, t_scene *scene);

/**
 * @brief Check if a filename has a specified extension.
 *
 * This function checks whether a given filename has a specified extension. It
 * compares the extension of the filename with the provided extension parameter.
 * The extension should be passed without the leading dot (e.g., "png" instead
 * of ".png"). If the filename has the same extension, the function returns true;
 * otherwise, it returns false.
 *
 * @param filename   The filename to check.
 * @param extension  The desired extension to compare with (without the leading
 *                   dot).
 * @return           True if the filename has the specified extension, false
 *                   otherwise.
 */
t_bool		check_extension(const char *filename, const char *extension);

////////////////////////////////////////////////////////////////////////////////
/// Parse element

/**
 * @brief Parses and processes an element from the input.
 *
 * This function parses and processes an element from the input by analyzing
 * the scanned sequence in the given scanner. It also updates the totals array
 * to keep track of the number of elements read from the input.
 *
 * @param scanner A pointer to the scanner structure.
 * @param scene   A pointer to the scene structure.
 * @param totals  An array to store the count of elements read from the input.
 * @return        A boolean value indicating whether the parse was successful.
 */
t_bool		parse_element(t_scanner *scanner, t_scene *scene, int totals[]);

/**
 * @brief Parse comments.
 *
 * @param scanner Pointer to the scanner.
 * @return        True if comment parsing is successful, false otherwise.
 */
t_bool		parse_comment(t_scanner *scanner);

/**
 * @brief Add a shape to the world.
 *
 * @param shape Pointer to the shape to be added.
 * @param world Pointer to the world.
 */
void		add_object_to_world(t_shape *shape, t_world *world);

/**
 * @brief Add a light source to the world.
 *
 * @param light Pointer to the light source to be added.
 * @param world Pointer to the world.
 */
void		add_light_to_world(t_light *light, t_world *world);

////////////////////////////////////////////////////////////////////////////////
/// Parse basic

/**
 * @brief Convert double from input and store in result.
 *
 * @param scanner Pointer to the scanner.
 * @param result  Pointer to store the parsed double.
 * @return        True if successful, false otherwise.
 */
t_bool		parse_double(t_scanner *scanner, double *result);

/**
 * @brief Parse the light ratio from the input.
 *
 * This function parses the light ratio from the input by analyzing the scanned
 * sequence in the given scanner. It verifies if the number is within the range
 * [0, 1]. If there is an error during parsing or if the number is outside the
 * valid range, the scanner is configured with the appropriate error message.
 *
 * @param scanner Pointer to the scanner of type t_scanner.
 * @param light   Pointer to the memory location where the parsed light ratio
 *                will be stored.
 * @return        True if successful, false otherwise. If false, check
 *                scanner->message for error message.
 */
t_bool		parse_light_ratio(t_scanner *scanner, double *light);

/**
 * @brief Convert field of view from input and store it in `fov`.
 *
 * This function converts the field of view from the input by analyzing the
 * scanned sequence in the given scanner and stores it in the memory location
 * pointed to by `fov`. It verifies if the field of view is within the range
 * of 0 to 180 degrees. If there is an error during conversion or if the value
 * is outside the valid range, the scanner is configured with the appropriate
 * error message.
 *
 * @param scanner Pointer to the scanner.
 * @param fov     Pointer to the memory location where the parsed field of view
 *                will be stored.
 * @return        True if successful, false otherwise. If false, check
 *                scanner->message for error message.
 */
t_bool		parse_field_of_view(t_scanner *scanner, int *fov);

/**
 * @brief Convert dimension from input and store it in `dimension`.
 *
 * This function converts the dimension from the input by analyzing the scanned
 * sequence in the given scanner and stores it in the memory location pointed to
 * by `dimension`. It verifies if the dimension is a positive number. If there is
 * an error during conversion or if the value is not positive, the scanner is
 * configured with the appropriate error message.
 *
 * @param scanner   Pointer to the scanner.
 * @param dimension Pointer to the memory location where the parsed dimension
 *                  will be stored.
 * @return          True if successful, false otherwise. If false, check
 *                  scanner->message for error message.
 */
t_bool		parse_dimension(t_scanner *scanner, double *dimension);

////////////////////////////////////////////////////////////////////////////////
/// Parse grouped

/**
 * @brief Convert a color from the input and store it in `result`.
 *
 * This function converts a color from the input by analyzing the scanned
 * sequence in the given scanner and stores it in the memory location pointed
 * to by `result`. It verifies if each color channel (red, green, and blue)
 * is between 0 and 255. If there is an error during conversion or if any
 * channel value is out of range, the scanner is configured with the
 * appropriate error message.
 *
 * @param scanner Pointer to the scanner.
 * @param result  Pointer to the memory location where the parsed color
 *                will be stored.
 * @return        True if successful, false otherwise. If false, check
 *                scanner->message for error message.
 */
t_bool		parse_color(t_scanner *scanner, t_color *result);

/**
 * @brief Convert a position from the input and store it in `position`.
 *
 * @param scanner  Pointer to the scanner object.
 * @param position Pointer to the memory location where the parsed position
 *                 will be stored.
 * @return         True if successful, false otherwise.
 */
t_bool		parse_position(t_scanner *scanner, t_point *position);

/**
 * @brief Convert a direction from the input and store it in `direction`.
 *
 * This function converts a direction vector from the input by analyzing the
 * scanned sequence in the given scanner and stores it in the memory location
 * pointed to by `direction`. It verifies if each component of the vector is
 * between -1 and 1.
 * If there is an error during conversion or if any component value is out of
 * range, the scanner is configured with the appropriate error message.
 *
 * @param scanner   Pointer to the scanner object.
 * @param direction Pointer to the memory location where the parsed direction
 *                  will be stored.
 * @return          True if successful, false otherwise. If false, check
 *                  scanner->message for error message.
 */
t_bool		parse_direction(t_scanner *scanner, t_vector *direction);

/**
 * @brief Parse a pattern from the input and assign it to a shape.
 *
 * @param scanner Pointer to the scanner object.
 * @param shape   Pointer to the shape to which the parsed pattern
 *                will be assigned.
 * @return        True if successful, false otherwise.
 */
t_bool		parse_pattern(t_scanner *scanner, t_shape *shape);

////////////////////////////////////////////////////////////////////////////////
/// Parse ambient

/**
 * @brief Convert ambient light from input and add to scene.
 *
 * @param scanner Pointer to the scanner object.
 * @param scene   Pointer to the scene to add ambient light.
 * @return        True if successful, false otherwise.
 */
t_bool		parse_ambient_light(t_scanner *scanner, t_scene *scene);

/**
 * @brief Convert camera from input and add to scene.
 *
 * @param scanner Pointer to the scanner object.
 * @param scene   Pointer to the scene to add camera.
 * @return        True if successful, false otherwise.
 */
t_bool		parse_camera(t_scanner *scanner, t_scene *scene);

/**
 * @brief Convert light point from input and add to scene.
 *
 * @param scanner Pointer to the scanner object.
 * @param scene   Pointer to the scene to add light point.
 * @return        True if successful, false otherwise.
 */
t_bool		parse_light(t_scanner *scanner, t_scene *scene);

////////////////////////////////////////////////////////////////////////////////
/// Parse shapes

/**
 * @brief Convert a sphere from the input and add it to the scene.
 *
 * This function converts a sphere from the input by analyzing the scanned
 * sequence in the given scanner and adds it to the scene. It uses the provided
 * scanner to parse the necessary properties of the sphere such as its position,
 * radius, color, pattern, and any additional attributes.
 *
 * @param scanner Pointer to the scanner.
 * @param scene   Pointer to the scene where the sphere will be added.
 * @return        True if the sphere is successfully parsed and added to the
 *                scene, false otherwise.
 */
t_bool		parse_sphere(t_scanner *scanner, t_scene *scene);

/**
 * @brief Convert a plane from the input and add it to the scene.
 *
 * This function converts a plane from the input by analyzing the scanned
 * sequence in the given scanner and adds it to the scene. It uses the provided
 * scanner to parse the necessary properties of the plane such as its position,
 * direction, color, pattern, and any additional attributes.
 *
 * @param scanner Pointer to the scanner.
 * @param scene   Pointer to the scene where the plane will be added.
 * @return        True if the plane is successfully parsed and added to the
 *                scene, false otherwise.
 */
t_bool		parse_plane(t_scanner *scanner, t_scene *scene);

/**
 * @brief Convert a cylinder from the input and add it to the scene.
 *
 * This function converts a cylinder from the input by analyzing the scanned
 * sequence in the given scanner and adds it to the scene. It uses the provided
 * scanner to parse the necessary properties of the cylinder such as its
 * position, direction, diameter, height, color, pattern, and any additional
 * attributes.
 *
 * @param scanner Pointer to the scanner.
 * @param scene   Pointer to the scene where the cylinder will be added.
 * @return        True if the cylinder is successfully parsed and added to the
 *                scene, false otherwise.
 */
t_bool		parse_cylinder(t_scanner *scanner, t_scene *scene);

/**
 * @brief Convert a cone from the input and add it to the scene.
 *
 * This function converts a cone from the input by analyzing the scanned
 * sequence in the given scanner and adds it to the scene. It uses the
 * provided scanner to parse the necessary properties of the cone such as
 * its position, direction, diameter, height, color, pattern, and any
 * additional attributes.
 *
 * @param scanner Pointer to the scanner.
 * @param scene   Pointer to the scene where the cone will be added.
 * @return        True if the cone is successfully parsed and added to the
 *                scene, false otherwise.
 */
t_bool		parse_cone(t_scanner *scanner, t_scene *scene);

////////////////////////////////////////////////////////////////////////////////
/// Parse utils

/**
 * @brief Display an error message based on the state of the scanner.
 *
 * @param scanner Pointer to the scanner.
 * @return        True if the error message is successfully displayed,
 *                false otherwise.
 */
t_bool		report_error(t_scanner *scanner);

/**
 * @brief Validate if a number is within a certain range.
 *
 * This function checks if the given value is within the specified range,
 * inclusive.
 *
 * @param value The value to be validated.
 * @param start The start of the range.
 * @param end   The end of the range.
 * @return      True if the value is within the range, false otherwise.
 */
t_bool		validate_range(double value, double start, double end);

/**
 * @brief Get the column where an error occurred.
 *
 * This function returns the column number where an error occurred during
 * scanning. It calculates the column number by subtracting the starting pointer
 * of the scanner (scanner->start) from the current pointer (scanner->current).
 * The result represents the offset in characters between the start of the input
 * and the current position where the error occurred.
 *
 * @param scanner Pointer to the scanner.
 * @return        The column number where an error occurred.
 */
int			get_error_column(t_scanner *scanner);

/**
 * @brief Determine the error message based on the state of the scanner.
 *
 * This function sets the error state of the scanner by assigning the provided
 * error message to the scanner's message field. It also resets the current
 * position in the scanner's input to the consume position, effectively
 * rewinding the scanner to a specific location.
 *
 * @param scanner       Pointer to the scanner object.
 * @param error_message The error message to be assigned to the scanner.
 */
void		set_error_state(t_scanner *scanner, const char *error_message);

////////////////////////////////////////////////////////////////////////////////
/// Parse textures

/**
 * @brief Validate and load a texture file into a UV map and assign it to the
 * shape.
 *
 * This function validates the integrity of the texture file to be scanned, loads
 * the file into a UV map, and assigns it to the specified shape.
 * The texture file is loaded into a UV map, which represents the mapping of the
 * texture coordinates onto the surface of the shape. The UV map allows for
 * accurate and realistic texture mapping, enhancing the visual appearance of
 * the shape.
 *
 * @param scanner Pointer to the scanner.
 * @param shape   Pointer to the shape to which the texture will be assigned.
 * @return        True if the texture file is successfully validated, loaded
 *                into the UV map, and assigned to the shape, false otherwise.
 */
t_bool		parse_texture(t_scanner *scanner, t_shape *shape);

#endif // !PARSER_H
