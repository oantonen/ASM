/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_put_float_f.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 17:33:49 by oantonen          #+#    #+#             */
/*   Updated: 2018/01/09 21:23:10 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hprintf.h"
#include <stdio.h>

char			*pf_float_entier_count(intmax_t nb, int *chars)
{
	int			i;
	intmax_t	nb2;
	char		*entier;

	nb2 = nb;
	i = 0;
	if (nb < 0)
		nb *= -1;
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	nb = nb2;
	*chars = i;
	if (MB_CUR_MAX == 4 && ISAPOSTROPHE)
	{
		*chars += (i > 3 && nb > 0) ? (i / 3) : 0;
		*chars = (i % 3 == 0 && i > 3) ? *chars - 1 : *chars;
	}
	entier = ft_strnew(*chars);
	ft_memset(entier, '0', *chars);
	return (entier);
}

char			*pf_float_f_entier(long double nb2)
{
	char		*entier;
	int			chars;
	int			i;
	intmax_t	nb;

	nb = (intmax_t)nb2;
	entier = pf_float_entier_count(nb, &chars);
	i = -1;
	(nb == 0) ? entier[0] = '0' : entier[0];
	if (nb < 0)
		nb = -nb;
	else if (nb == 0)
		return (entier);
	while (nb > 0)
	{
		if (ISAPOSTROPHE == 1 && ++i != 0 && !(i % 3) && MB_CUR_MAX == 4)
			entier[--chars] = ',';
		entier[--chars] = nb % 10 + 48;
		nb = nb / 10;
	}
	return (entier);
}

long double		pf_round_float(long double nb, int prec, t_float_cast d1)
{
	long double	fraction;
	int			first_digit;

	fraction = nb - (size_t)nb;
	while (prec-- > 0)
	{
		first_digit = (int)(fraction * 10);
		fraction = fraction * 10 - first_digit;
	}
	if (FLT_ROUNDS == 1)
	{
		if (prec == -1 && fraction > 0.5)
			nb = nb + pf_float_sqrt(0.1, g_mode.prec);
		else if (prec == -1 && fraction == 0.5)
			nb = (pf_check_even(nb) == TRUE) ? nb : nb + 0.5;
	}
	else if (FLT_ROUNDS == 2)
	{
		if (!d1.parts.sign)
			nb += (fraction > 0) ? pf_float_sqrt(0.1, g_mode.prec) : 0.0;
	}
	return (nb);
}

char			*pf_float_f_fraction(long double nb, t_float_cast d1)
{
	long double		fraction;
	int				first_digit;
	int				i;
	char			*res;

	(g_mode.prec == 0 && ISDOT == 0) ? g_mode.prec += 6 : g_mode.prec;
	nb = (nb < 0) ? -nb : nb;
	nb = pf_round_float(nb, g_mode.prec, d1);
	i = 1;
	if (g_mode.prec == 0 && ISDOT == 1 && ISHASH == 0)
		return (ft_strjoin(pf_float_f_entier(nb), ""));
	res = ft_strnew(g_mode.prec + 1);
	fraction = (nb - (size_t)nb) * 10;
	res[0] = '.';
	while (i < g_mode.prec + 1)
	{
		first_digit = (int)fraction;
		res[i] = first_digit + 48;
		fraction = (fraction - first_digit) * 10;
		i++;
	}
	return (ft_strjoin(pf_float_f_entier(nb), res));
}

char			*pf_put_float_f(va_list ap)
{
	int				len;
	char			*s;
	t_float_cast	d1;
	long double		nb;
	char			*pref;

	nb = (ISLD) ? va_arg(ap, long double) : va_arg(ap, double);
	d1.f = (double)nb;
	s = pf_float_f_fraction((long double)nb, d1);
	len = ft_strlen(s);
	if (ISZERO && d1.parts.exponent == 2047)
		g_mode.flags &= ~(1UL << 4);
	pref = (ISPLUS && nb >= 0) ? "+" : "";
	pref = (ISSPACE && nb >= 0 && !ISPLUS) ? " " : pref;
	pref = (d1.parts.sign) ? "-" : pref;
	if (d1.parts.mantisa == 2251799813685248 && d1.parts.exponent == 2047)
		pref = "";
	if ((len = ft_strlen(pf_float_inf_nan(d1))) != 0)
		return (pf_final_modify(pf_float_inf_nan(d1), len, g_mode.width, pref));
	return (pf_final_modify(s, ft_strlen(s), g_mode.width, pref));
}
