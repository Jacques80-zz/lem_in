/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 18:48:38 by jdouniol          #+#    #+#             */
/*   Updated: 2017/11/29 02:16:59 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
**	Alloue avec malloc(3) et retourne un tableau de chaines de caracteres
**	"fraiches" (toutes terminees par un '\0', le tableau egalement donc)
**	resultant de la decoupe de s selon le caractere c. Si l'allocation echoue,
**	la fonction retourne NULL.
*/

static	int	nbr_word(char const *s, char c)
{
	int		nbr;
	char	before;

	nbr = 0;
	before = c;
	while (*s)
	{
		if (*s && *s != c && before == c)
			nbr++;
		before = *s;
		s++;
	}
	return (nbr);
}

char		**ft_strsplit(char const *s, char c)
{
	int		word;
	char	**words;
	int		start;
	int		end;

	word = 0;
	if (!s || !(words = (char **)malloc(sizeof(char *) * (nbr_word(s, c) + 1))))
		return (NULL);
	start = 0;
	while (s[start])
	{
		if (s[start] != c && s[start] != '\0')
		{
			end = start;
			while (s[end] != c && s[end])
				end++;
			if (!(words[word++] = ft_strsub(s, start, end - start)))
				return (NULL);
			start = end - 1;
		}
		start++;
	}
	words[word] = 0;
	return (words);
}
