/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:11:15 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/18 10:14:22 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H

# include <fcntl.h>

# include "world.h"
# include "canvas.h"

# define ERROR_UNEXPECTED_ELEMENT "Unexpected element"
# define ERROR_EXPECTED_NUMBER "Expected a number"
# define ERROR_EXPECTED_NEWLINE "Expected newline"
# define ERROR_EXPECTED_COMMA "Expected a comma"

# define INVALID_NUMBER "Invalid number"
# define INVALID_VECTOR "Vector components must be between -1 and 1.\n"
# define INVALID_COLOR "Color values must be between 0 and 255.\n"
# define INVALID_LIGHT "Light ratio must be between -1 and 1.\n"
# define INVALID_FOV "Field of view must be between 0 and 180.\n"
# define INVALID_DIMENSION "Dimensions should be positive.\n"

typedef struct s_scene
{
	t_canvas	canvas;
	t_world		world;
	t_camera	camera;
}	t_scene;

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
	TOKEN_ERROR
}	t_token;

typedef struct s_scanner
{
	int			line;
	const char	*start;
	const char	*consume;
	const char	*current;
	const char	*message;
}	t_scanner;

// Scanner
t_scanner	new_scanner(const char *source);
void		init_scanner(t_scanner *scanner, const char *source);
t_bool		scan_integer(t_scanner *scanner);
t_bool		scan_float(t_scanner *scanner);
t_bool		scan_comma(t_scanner *scanner);
t_bool		scan_newline(t_scanner *scanner);

// Scanner types
t_token		parse_type(t_scanner *scanner);

// Scanner utils
void		advance(t_scanner *scanner);
void		skip_whitespace(t_scanner *scanner);
int			is_sign(int c);

// Parse
// t_bool		parse_element(t_scanner *scanner);
t_bool		parse_element(t_scanner *scanner, t_scene *scene);
void		add_to_world(t_shape *shape, t_world *world);

// Parse compounds
t_bool		parse_float(t_scanner *scanner, float *result);
t_bool		parse_color(t_scanner *scanner, t_color *result);
t_bool		parse_position(t_scanner *scanner, t_point *position);
t_bool		parse_direction(t_scanner *scanner, t_vector *direction);
t_bool		parse_dimension(t_scanner *scanner, float *dimension);
t_bool		parse_field_of_view(t_scanner *scanner, int *fov);
t_bool		parse_light_ratio(t_scanner *scanner, float *light);

t_bool		parse_ambient_light(t_scanner *scanner, t_scene *scene);
t_bool		parse_camera(t_scanner *scanner, t_scene *scene);
t_bool		parse_light(t_scanner *scanner, t_scene *scene);
t_bool		parse_sphere(t_scanner *scanner, t_scene *scene);
t_bool		parse_plane(t_scanner *scanner, t_scene *scene);
t_bool		parse_cylinder(t_scanner *scanner, t_scene *scene);
t_bool		parse_comment(t_scanner *scanner);

// Parse utils
t_bool		report_error(t_scanner *scanner);
t_bool		validate_range(float value, float start, float end);
int			get_error_column(t_scanner *scanner);
void		set_error_state(t_scanner *scanner, const char *error_message);

// Helpers
double		ft_atof(const char *nptr);
void		*ft_realloc(void *ptr, size_t size);

#endif // !PARSER_H
