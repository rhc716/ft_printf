/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 21:24:14 by hroh              #+#    #+#             */
/*   Updated: 2020/11/10 02:06:27 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	set_prec(t_option *opt, const char *format, va_list ap)
{
	opt->dot = 1;
	opt->i++;
	if (format[opt->i] == '*')
	{
		opt->prec = va_arg(ap, int);
		opt->i++;
	}
	else
	{
		opt->prec = ft_atoi(&format[opt->i]);
		if (opt->prec == 0)
		{
			opt->prec = -1;
			return ;
		}
		opt->i += ft_nbrlen(opt->prec);
	}
}

static void	set_width(t_option *opt, const char *format, va_list ap)
{
	if (format[opt->i] == '*')
	{
		opt->width = va_arg(ap, int);
		opt->i++;
	}
	else
	{
		opt->width = ft_atoi(&format[opt->i]);
		opt->i += ft_nbrlen(opt->width);
	}
}

static void	set_option(t_option *opt, const char *format, va_list ap)
{
	if (format[opt->i] == '0' && opt->width == 0 && opt->dot == 0)
	{
		opt->zero = 1;
		opt->i++;
	}
	else if (format[opt->i] == '-' && opt->width == 0 && opt->dot == 0)
	{
		opt->minus = 1;
		opt->i++;
	}
	else if ((ft_isdigit(format[opt->i]) || format[opt->i] == '*')
		&& format[opt->i] != '0' && opt->dot == 0)
		set_width(opt, format, ap);
	else if (format[opt->i] == '.')
		set_prec(opt, format, ap);
	else
		opt->i++;
}

void		parse_option(t_option *opt, const char *format, va_list ap)
{
	while (format[opt->i] && !(ft_strchr("cspdiuxXf%", format[opt->i])))
		set_option(opt, format, ap);
	if (ft_strchr("cspdiuxXf%", format[opt->i]))
		opt->conv = format[opt->i++];
	if (opt->prec >= 0 && opt->dot == 1 && opt->conv != '%')
		opt->zero = 0;
	if (opt->prec == 0 && opt->dot == 1)
		opt->prec = -1;
	if ((opt->minus == 1 || opt->prec == -1) && opt->conv != '%')
		opt->zero = 0;
	if (opt->width < 0)
	{
		opt->minus = 1;
		opt->width *= -1;
	}
	if (opt->conv == 'x' || opt->conv == 'X' || opt->conv == 'p')
		opt->base = 16;
}
