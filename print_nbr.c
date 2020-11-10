/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 21:31:56 by hroh              #+#    #+#             */
/*   Updated: 2020/11/11 04:50:57 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	set_prec_nbr(unsigned long long nbr, t_option *opt, char **buf)
{
	int	buf_len;
	int	sum;
	int	i;

	buf_len = (nbr == 0 && opt->prec != -1
	&& opt->conv != 'p') ? 1 : ft_nbrlen_base(nbr, opt);
	sum = (opt->prec > buf_len) ? opt->prec : buf_len;
	if (!(*buf = (char *)malloc(sizeof(char) * sum + 1)))
		return (0);
	i = 0;
	(*buf)[sum] = '\0';
	while (i < sum - buf_len)
		(*buf)[i++] = '0';
	i = 1;
	if (nbr == 0 && opt->prec != -1 && opt->conv != 'p')
		(*buf)[sum - i] = '0';
	while (nbr)
	{
		(*buf)[sum - i++] = ft_baseset(opt->conv)[nbr % opt->base];
		nbr /= opt->base;
	}
	return (buf_len);
}

static int	set_sign(t_option *opt, char **buf, int pos, int buf_len)
{
	int	len;

	len = 0;
	if (pos == 0 && (opt->conv == 'i' || opt->conv == 'd') &&
		opt->zero == 0 && opt->sign == -1)
	{
		*buf = ft_strjoin("-", *buf, 2);
		len = 1;
	}
	if (pos == 1 && opt->sign == -1 && opt->zero == 1)
	{
		if (buf_len >= opt->width)
		{
			*buf = ft_strjoin("-", *buf, 2);
			len = 1;
		}
		else if (buf_len < opt->width)
			*buf[0] = '-';
	}
	return (len);
}

static int	set_prefix(char **buf, unsigned long long nbr, t_option *opt)
{
	if (nbr == 0 && (opt->prec == 0 || opt->prec <= -2))
	{
		*buf = ft_strjoin("0x0", *buf, 2);
		return (3);
	}
	*buf = ft_strjoin("0x", *buf, 2);
	return (2);
}

static void	put_width_str(char **buf, t_option *opt)
{
	char	*width;
	int		i;
	int		size;

	size = opt->width - (int)ft_strlen(*buf);
	if (size <= 0)
		return ;
	width = (char *)malloc(sizeof(char) * (size + 1));
	i = 0;
	while (i < size)
		width[i++] = (opt->zero == 1) ? '0' : ' ';
	width[i] = '\0';
	if (opt->minus == 0)
		*buf = ft_strjoin(width, *buf, 3);
	else
		*buf = ft_strjoin(*buf, width, 3);
}

void		print_nbr(unsigned long long nbr, t_option *opt)
{
	char	*buf;
	int		buf_len;

	if ((opt->conv == 'd' || opt->conv == 'i') && (int)nbr < 0)
	{
		opt->sign = -1;
		nbr = -nbr;
	}
	buf_len = set_prec_nbr(nbr, opt, &buf);
	buf_len += set_sign(opt, &buf, 0, 0);
	if (opt->conv == 'p')
		buf_len += set_prefix(&buf, nbr, opt);
	put_width_str(&buf, opt);
	set_sign(opt, &buf, 1, buf_len);
	ft_putstr(buf);
	opt->ret += (int)ft_strlen(buf);
	free(buf);
}
