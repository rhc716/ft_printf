/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 21:30:12 by hroh              #+#    #+#             */
/*   Updated: 2020/11/06 21:36:26 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_char_pad(t_option *opt)
{
	int i;

	i = 0;
	while (i < opt->width)
	{
		if (opt->zero == 1)
			ft_putchar('0');
		else
			ft_putchar(' ');
		i++;
		opt->ret++;
	}
}

void		print_char(int c, t_option *opt)
{
	if (opt->conv == '%' && opt->minus == 1)
		opt->zero = 0;
	if (opt->minus == 1)
		opt->ret += ft_putchar(c);
	print_char_pad(opt);
	if (opt->minus == 0)
		opt->ret += ft_putchar(c);
}
