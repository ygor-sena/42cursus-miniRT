/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:37:04 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/18 16:32:05 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#define RED "\033[31;1m"
#define BOLD "\033[1m"
#define RESET "\033[m"

void	display_position(t_scanner *scanner, int line, int column);

t_bool	report_error(t_scanner *scanner)
{
	int		line;
	int		column;
	char	*position;

	line = scanner->line;
	column = get_error_column(scanner) + 1;
	position = BOLD"%s at line %d, column %d:\n"RESET;
	ft_putendl_fd("Error", STDOUT_FILENO);
	printf(position, scanner->message, line, column);
	display_position(scanner, line, column);
	return (FALSE);
}

void	set_error_state(t_scanner *scanner, const char *error_message)
{
	scanner->message = error_message;
	scanner->current = scanner->consume;
}

void	display_position(t_scanner *scanner, int line, int column)
{
	printf("%5d | %s%5s | ", line, scanner->start, " ");
	while (--column > 0)
		printf(" ");
	printf(RED"^\n"RESET);
}

t_bool	validate_range(float value, float start, float end)
{
	if (value >= start && value <= end)
		return (TRUE);
	return (FALSE);
}

int	get_error_column(t_scanner *scanner)
{
	return (scanner->current - scanner->start);
}
