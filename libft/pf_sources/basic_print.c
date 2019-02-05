/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 20:05:54 by fallouch          #+#    #+#             */
/*   Updated: 2019/02/05 15:53:30 by fallouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_putnc(char c, int n)
{
	if (n < 0)
		n = 0;
	while (n--)
		ft_putc(c);
}

void		ft_puts(char *str)
{
	if (!str)
		return ;
	while (*str)
		ft_putc(*str++);
}

void		ft_put_str(char *str, t_printf pf)
{
	if (!str)
		str = "(null)";
	pf.width -= ft_min(ft_strlen(str), pf.precision);
	!pf.moins ? ft_putwidth(pf.width, pf) : 1;
	if (pf.precision > 0 || pf.precision == -1)
	{
		while (*str && (pf.precision || pf.precision == -1))
		{
			ft_putc(*str++);
			pf.precision--;
		}
	}
	pf.moins ? ft_putwidth(pf.width, pf) : 1;
}

void		ft_put_chr(char c, t_printf pf)
{
	!pf.moins ? ft_putwidth(pf.width - 1, pf) : 1;
	ft_putc(c);
	pf.moins ? ft_putwidth(pf.width - 1, pf) : 1;
}
