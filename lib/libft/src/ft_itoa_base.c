/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:35:57 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/09/14 17:37:03 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbrlen(unsigned long n, unsigned long base);

char	*ft_itoa_base(unsigned long nbr, char *nbr_sys)
{
	char	*str;
	int		len;
	int		base;

	base = ft_strlen(nbr_sys);
	len = nbrlen(nbr, base);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = nbr_sys[nbr % base];
		nbr /= base;
	}
	return (str);
}

static int	nbrlen(unsigned long n, unsigned long base)
{
	if (n < base)
		return (1);
	n /= base;
	return (nbrlen(n, base) + 1);
}
