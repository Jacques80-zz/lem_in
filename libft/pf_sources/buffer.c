/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fallouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 14:34:09 by fallouch          #+#    #+#             */
/*   Updated: 2019/02/05 15:53:43 by fallouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		g_buffer[PF_BUFF_SIZE + 1] = {0};
int			g_index = 0;

void		ft_putc(char c)
{
	counter(0);
	g_buffer[g_index++] = c;
	if (g_index == PF_BUFF_SIZE)
		print_buffer();
}

void		print_buffer(void)
{
	write(1, g_buffer, g_index);
	while (g_index >= 0)
		g_buffer[g_index--] = 0;
	g_index = 0;
}
