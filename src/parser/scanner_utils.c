/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:12:46 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/06/11 10:11:38 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	advance(t_scanner *scanner)
{
	scanner->current++;
}

void	skip_whitespace(t_scanner *scanner)
{
	while (*scanner->current == ' ')
		advance(scanner);
	scanner->consume = scanner->current;
}

int	is_sign(int c)
{
	return (c == '-' || c == '+');
}

void	save_position(t_scanner *scanner)
{
	skip_whitespace(scanner);
	scanner->sync = scanner->consume;
}

void	sync_position(t_scanner *scanner)
{
	scanner->consume = scanner->sync;
}
