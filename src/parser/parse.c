/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:15:21 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/06/08 21:18:20 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#ifndef EINVAL
# define EINVAL 22  /* Invalid argument */
#endif

#ifndef ENOENT
# define ENOENT 2   /* No such file or directory */
#endif

static int		open_rt_file(const char *filename);
static t_bool	flush_buffer(int file);
static t_bool	validate_restrictions(int totals[]);

t_bool	parse(char *filename, t_scene *scene)
{
	int			file;
	char		*content;
	t_scanner	scanner;
	static int	totals[TOKEN_COUNT];

	file = open_rt_file(filename);
	content = get_next_line(file);
	while (content)
	{
		init_scanner(&scanner, content);
		if (!parse_element(&scanner, scene, totals))
		{
			report_error(&scanner);
			free(content);
			return (flush_buffer(file));
		}
		free(content);
		content = get_next_line(file);
	}
	close(file);
	return (validate_restrictions(totals));
}

static int	open_rt_file(const char *filename)
{
	int		file;
	char	error_msg[BUFFER];

	ft_strlcpy(error_msg, "minirt: ", BUFFER);
	if (!check_extension(filename, "rt"))
	{
		ft_strlcat(error_msg, strerror(EINVAL), BUFFER);
		ft_putendl_fd(error_msg, STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
	file = open(filename, O_RDONLY);
	if (file < 0)
	{
		ft_strlcat(error_msg, strerror(ENOENT), BUFFER);
		ft_putendl_fd(error_msg, STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
	return (file);
}

t_bool	check_extension(const char *filename, const char *extension)
{
	const char	*file_ext;

	file_ext = ft_strrchr(filename, '.');
	if (file_ext)
	{
		file_ext++;
		if (ft_strncmp(file_ext, extension, ft_strlen(extension) + 1) == 0)
			return (TRUE);
	}
	return (FALSE);
}

static t_bool	flush_buffer(int file)
{
	char	*content;

	content = "";
	close(file);
	while (content)
	{
		content = get_next_line(file);
		free(content);
	}
	return (FALSE);
}

static t_bool	validate_restrictions(int totals[])
{
	t_bool	has_error;
	char	error_msg[BUFFER];

	has_error = FALSE;
	ft_strlcpy(error_msg, "Error\n", BUFFER);
	if (totals[TOKEN_CAMERA] > 1)
	{
		has_error = TRUE;
		ft_strlcat(error_msg, ERROR_CAMERA, BUFFER);
	}
	if (totals[TOKEN_AMBIENT_LIGHT] > 1)
	{
		has_error = TRUE;
		ft_strlcat(error_msg, ERROR_AMBIENT, BUFFER);
	}
	if (has_error)
		ft_putstr_fd(error_msg, STDERR_FILENO);
	return (!has_error);
}
