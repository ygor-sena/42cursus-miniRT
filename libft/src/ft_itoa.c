/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:04:53 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/07/11 13:14:12 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digits(unsigned int n);

char	*ft_itoa(int n)
{
	char			*str;
	int				len;
	int				negative;
	unsigned int	nb;

	nb = n;
	negative = (n < 0);
	if (negative)
		nb = n * (-1);
	len = digits(nb) + negative;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = (nb % 10) + '0';
		nb /= 10;
	}
	if (negative)
		str[0] = '-';
	return (str);
}

static int	digits(unsigned int n)
{
	if (n < 10)
		return (1);
	return (digits(n / 10) + 1);
}
