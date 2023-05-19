/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:36:22 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/05/15 16:42:39 by mdias-ma         ###   ########.fr       */
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

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (ft_calloc(1, size));
	new_ptr = ft_calloc(1, size);
	if (new_ptr != NULL)
	{
		ft_memcpy(new_ptr, ptr, size);
		free(ptr);
	}
	return (new_ptr);
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
