/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 21:30:51 by hroh              #+#    #+#             */
/*   Updated: 2020/11/06 21:38:22 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_str_pad(t_option *opt, int lpad, int arglen)
{
	int	i;
	int	padlen;

	i = 0;
	if (opt->prec > 0 && opt->prec < arglen)
		padlen = opt->width - opt->prec;
	else
		padlen = opt->width - arglen;
	if (opt->prec == -1)
		padlen += arglen;
	if (opt->width && ((!lpad && opt->minus) ||
				(lpad && !opt->minus)))
	{
		while (++i <= padlen)
			ft_putchar(' ');
		opt->ret += i - 1;
	}
}

void		print_str(char *arg, t_option *opt)
{
	int	i;

	i = 0;
	if (!arg)
		arg = "(null)";
	if (opt->width || opt->prec)
		print_str_pad(opt, 1, ft_strlen(arg));
	if (opt->prec > 0)
	{
		while (i < opt->prec && arg[i])
			ft_putchar(arg[i++]);
		opt->ret += i;
	}
	else if (opt->prec != -1)
	{
		ft_putstr(arg);
		opt->ret += ft_strlen(arg);
	}
	if (opt->width && opt->minus)
		print_str_pad(opt, 0, ft_strlen(arg));
}
