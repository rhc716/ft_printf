/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:23:55 by hroh              #+#    #+#             */
/*   Updated: 2020/11/11 02:32:02 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>
# include "./libft/libft.h"

typedef struct	s_option
{
	int			zero;
	int			minus;
	int			width;
	int			dot;
	int			prec;
	char		conv;
	int			base;
	int			sign;
	int			i;
	int			ret;
}				t_option;

int				ft_printf(const char *format, ...);
void			parse_option(t_option *opt, const char *format, va_list ap);
void			print_char(int c, t_option *opt);
void			print_nbr(unsigned long long nbr, t_option *opt);
void			print_str(char *arg, t_option *opt);
void			init_option(t_option *opt);
int				ft_nbrlen_base(unsigned long long nbr, t_option *opt);
char			*ft_baseset(char type);

#endif
