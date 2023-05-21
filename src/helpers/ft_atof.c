/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:36:22 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/21 16:23:07 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		get_sign(const char **nptr);
static double	convert_fractional_part(const char *nptr);

double	ft_atof(const char *nptr)
{
	int		sign;
	double	result;

	result = 0.0;
	sign = get_sign(&nptr);
	while (*nptr != '\0' && *nptr != '.')
	{
		if (ft_isdigit(*nptr))
			result = result * 10.0 + (*nptr - '0');
		else
			return (result * sign);
		nptr++;
	}
	result += convert_fractional_part(nptr);
	return (result * sign);
}

static double	convert_fractional_part(const char *nptr)
{
	double	result;
	double	fraction;

	result = 0.0;
	fraction = 0.1;
	if (*nptr == '.')
	{
		nptr++;
		while (ft_isdigit(*nptr))
		{
			result += (*nptr - '0') * fraction;
			fraction *= 0.1;
			nptr++;
		}
	}
	return (result);
}

static int	get_sign(const char **nptr)
{
	while (ft_isspace(**nptr))
		(*nptr)++;
	if (**nptr == '-')
	{
		(*nptr)++;
		return (-1);
	}
	else if (**nptr == '+')
		(*nptr)++;
	return (1);
}
