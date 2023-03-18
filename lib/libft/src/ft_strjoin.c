/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 11:21:22 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/06/12 11:57:38 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define NUL 1

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	s1len;
	size_t	s2len;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	newstr = malloc(s1len + s2len + NUL);
	if (!newstr)
		return (NULL);
	ft_strlcpy(newstr, s1, s1len + NUL);
	ft_strlcpy(newstr + s1len, s2, s2len + NUL);
	return (newstr);
}
