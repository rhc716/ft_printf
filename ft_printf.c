/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:01:05 by hroh              #+#    #+#             */
/*   Updated: 2020/11/11 01:31:08 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_format(t_option *opt, va_list ap)
{
	if (opt->conv == '%')
		print_char('%', opt);
	else if (opt->conv == 'c')
		print_char(va_arg(ap, int), opt);
	else if (opt->conv == 's')
		print_str(va_arg(ap, char *), opt);
	else if (opt->conv == 'd' || opt->conv == 'i')
		print_nbr(va_arg(ap, int), opt);
	else if (opt->conv == 'u' || opt->conv == 'x' || opt->conv == 'X')
		print_nbr(va_arg(ap, unsigned int), opt);
	else if (opt->conv == 'p')
		print_nbr(va_arg(ap, unsigned long long), opt);
}

static void	read_format(const char *format, va_list ap, t_option *opt)
{
	opt->i = 0;
	opt->ret = 0;
	while (format[opt->i])
	{
		if (format[opt->i] == '%')
		{
			opt->i++;
			init_option(opt);
			parse_option(opt, format, ap);
			print_format(opt, ap);
		}
		else
		{
			ft_putchar(format[opt->i]);
			opt->i++;
			opt->ret++;
		}
	}
}

int			ft_printf(const char *format, ...)
{
	va_list		ap;
	t_option	*opt;
	int			ret;

	if (!format)
		return (-1);
	if (!(opt = malloc(sizeof(t_option))))
		return (-1);
	va_start(ap, format);
	read_format(format, ap, opt);
	ret = opt->ret;
	va_end(ap);
	return (ret);
}
