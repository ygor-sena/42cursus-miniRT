/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:07:51 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/06/10 15:25:32 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	t_byte	*blk1;
	t_byte	*blk2;

	if (!n)
		return (0);
	blk1 = (t_byte *)s1;
	blk2 = (t_byte *)s2;
	while (*blk1 == *blk2 && --n)
	{
		blk1++;
		blk2++;
	}
	return (*blk1 - *blk2);
}
