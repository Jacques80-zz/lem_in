/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 14:02:26 by jdouniol          #+#    #+#             */
/*   Updated: 2017/11/22 16:50:57 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int		ft_is_space(char c)
{
	return (c == '\n' || c == '\t' || c == ' ' || c == '\0');
}

static char		*ft_strdup(char *src)
{
	int		size;
	int		i;
	char	*ptr;

	i = 0;
	size = 0;
	while (src[size] != '\0')
		size++;
	ptr = malloc(sizeof(*src) * (size + 1));
	while (i < size)
	{
		ptr[i] = src[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

static int		ft_word(char *str, int w)
{
	if (w == 0)
		return (!ft_is_space(str[w]));
	else
		return (ft_is_space(str[w - 1] && !ft_is_space(str[w])));
}

char			**ft_split_whitespaces(char *str)
{
	int		w;
	int		i;
	char	*line;
	char	**array;
	int		words;

	words = 0;
	w = 0;
	line = ft_strdup(str);
	while (str[w++])
		if (ft_word(str, w))
			words++;
	array = malloc(sizeof(char*) * words);
	w = 0;
	i = 0;
	while (str[w])
	{
		if (ft_is_space(line[w]))
			line[w] = '\0';
		else if (ft_word(line, w))
			array[i++] = line + w;
		array[i] = NULL;
		w++;
	}
	return (array);
}
