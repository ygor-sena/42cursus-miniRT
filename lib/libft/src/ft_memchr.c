/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:47:49 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/06/20 17:16:59 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	t_byte	*aux;

	aux = (t_byte *)s;
	while (n--)
	{
		if (*aux == (t_byte)c)
			return (aux);
		aux++;
	}
	return (NULL);
}
