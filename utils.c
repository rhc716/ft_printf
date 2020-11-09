/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 21:34:29 by hroh              #+#    #+#             */
/*   Updated: 2020/11/09 22:00:15 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_nbrlen_base(unsigned long long nbr, t_option *opt)
{
	int		i;

	if (nbr == 0 && opt->prec != 0)
		return (1);
	i = 0;
	while (nbr)
	{
		i++;
		nbr /= opt->base;
	}
	return (i);
}

void	init_option(t_option *opt)
{
	opt->zero = 0;
	opt->minus = 0;
	opt->width = 0;
	opt->dot = 0;
	opt->prec = 0;
	opt->conv = 0;
	opt->base = 10;
	opt->sign = 1;
}

char	*ft_baseset(char type)
{
	if (type == 'u' || type == 'd' || type == 'i')
		return ("0123456789");
	else if (type == 'x' || type == 'p')
		return ("0123456789abcdef");
	else if (type == 'X')
		return ("0123456789ABCDEF");
	return (0);
}
