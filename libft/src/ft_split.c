/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:26:20 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/06/22 11:27:59 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c);
static void		cut_words(char const *s, char c, char **str_arr, size_t words);

char	**ft_split(char const *s, char c)
{
	size_t	words;
	char	**str_arr;

	words = count_words(s, c);
	str_arr = malloc((words + 1) * sizeof(*str_arr));
	if (!str_arr)
		return (NULL);
	cut_words(s, c, str_arr, words);
	str_arr[words] = NULL;
	return (str_arr);
}

static void	cut_words(char const *s, char c, char **str_arr, size_t words)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	while (k < words)
	{
		while ((s[i + j] != c) && s[i] && s[i + j])
			j++;
		if (j > 0)
		{
			str_arr[k++] = ft_substr(s, i, j);
			i += j;
			j = 0;
		}
		else
			i++;
	}
}

static size_t	count_words(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	words;

	i = 0;
	j = 0;
	words = 0;
	while (s[i])
	{
		while ((s[i + j] != c) && s[i + j])
			j++;
		if (j > 0)
		{
			i += j;
			j = 0;
			words++;
		}
		else
			i++;
	}
	return (words);
}
