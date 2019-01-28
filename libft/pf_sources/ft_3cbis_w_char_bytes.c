/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_w_char_bytes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 14:43:34 by jdouniol          #+#    #+#             */
/*   Updated: 2018/11/04 14:36:22 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

/*
**	ft_one_byte applique itoa base 2 pour ecrire un str, appliquable jusqu'a 127
*/

char	*ft_one_byte(wchar_t wc)
{
	char	*bin;

	bin = ft_itoa_base(wc + 0x80, 2);
	bin[0] = '0';
	return (bin);
}

/*
**	ft_three_bytes applique itoa_base_ll pr ecrire la str qui contient 3 bytes
**	avec ft_strjoinclr 2 fois successivement et renvoie une nouvelle str
**	s1 = itoa_base_ll 2 wc decale de 18 + 192
**	s2 = itoa_base_ll 2 wc decale de 12 & (and) 63 (soit "6*1") + 128
**	s3 = itoa_base_ll 2 wc decale de 6 & (and) 63 (soit 6*1) + 128
**	s4 = itoa_base_ll 2 wc & (and) 63 (soit 6*1) + 128
*/

char	*ft_four_bytes(wchar_t wc)
{
	char	*bin;
	char	*(*f)(unsigned long long, unsigned int);

	f = &ft_itoa_base_ll;
	bin = ft_strjoin_clr(f((wc >> 18) + 0xF0, 2),
			f(((wc >> 12) & 0x3f) + 0x80, 2));
	bin = ft_strjoin_clr(bin, f(((wc >> 6) & 0x3f) + 0x80, 2));
	bin = ft_strjoin_clr(bin, f((wc & 0x3F) + 0x80, 2));
	return (bin);
}

/*
**	ft_three_bytes applique itoa_base_ll pr ecrire la str qui contient 3 bytes
**	avec ft_strjoinclr 2 fois successivement et renvoie une nouvelle str
**	s1 = itoa_base_ll 2 wc decale de 12 + 192
**	s2 = itoa_base_ll 2 wc decale de 6 & (and) 63 (soit "6*1") + 128
**	s3 = itoa_base_ll 2 wc & (and) 63 (soit 6*1) + 128
*/

char	*ft_three_bytes(wchar_t wc)
{
	char			*bin;
	unsigned long	x;
	char			*(*f)(unsigned long long, unsigned int);

	f = &ft_itoa_base_ll;
	bin = ft_strjoin_clr(f((wc >> 12) + 0xE0, 2),
			f(((wc >> 6) & 0x3F) + 0x80, 2));
	x = (wc & 0x3F) + 0x80;
	bin = ft_strjoin_clr(bin, f(x, 2));
	return (bin);
}

/*
**	ft_two_byte applique itoa base 2 pour ecrire la str qui contient 2 bytes
**	avec ft_strjoin_clr qui concatene s1 et s2 et renvoie une nouuvelle str
**	s1 = itoa_base 2 wc decale de 6 + 192
**	s2 = ito_base 2 wc &(and) 63 (soit "6*1") + 128
*/

char	*ft_two_bytes(wchar_t wc)
{
	char	*bin;

	bin = ft_strjoin_clr(ft_itoa_base((wc >> 6) + 0xC0, 2),
				ft_itoa_base((wc & 0x3F) + 0x80, 2));
	return (bin);
}
