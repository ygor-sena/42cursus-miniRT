/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 12:08:20 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/06/11 09:27:36 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem_blk;
	int		blk_size;

	blk_size = nmemb * size;
	if (!blk_size || blk_size / size != nmemb)
		return (NULL);
	mem_blk = malloc(blk_size);
	if (!mem_blk)
		return (NULL);
	ft_bzero(mem_blk, blk_size);
	return (mem_blk);
}
