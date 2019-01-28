/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_match.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 13:46:33 by jdouniol          #+#    #+#             */
/*   Updated: 2018/10/30 13:46:37 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_match(const char *s1, const char *s2)
{
	if (!*s1 && !*s2)
		return (1);
	else if (*s1 == *s2 && *s1 != '*')
		return (ft_match(s1 + 1, s2 + 1));
	else if (*s1 == '*' && *s2 == '*')
		return (ft_match(s1 + 1, s2));
	else if (*s2 == '*' && !*s1)
		return (ft_match(s1, s2 + 1));
	else if (*s2 == '*' && *s2 && *s1)
		return (ft_match(s1, s2 + 1) || ft_match(s1 + 1, s2));
	else
		return (0);
}
