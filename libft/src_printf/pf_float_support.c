/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_float_support.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 16:43:37 by oantonen          #+#    #+#             */
/*   Updated: 2018/01/11 20:35:35 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hprintf.h"

double		pf_float_sqrt(long double sample, int g_prec)
{
	int		prec2;

	prec2 = g_prec;
	if (prec2 == 0)
		sample = 1.0;
	if (prec2 != 0)
		while (--prec2 != 0)
			sample = sample / 10;
	return (sample);
}

int			pf_check_even(long double nb)
{
	int		nb2;

	nb2 = (int)nb;
	if ((nb2 & 1U) == 1)
		return (FALSE);
	return (TRUE);
}

char		*pf_float_inf_nan(t_float_cast d1)
{
	char	*res;

	res = ft_strnew(3);
	if (d1.parts.exponent == 2047 && d1.parts.mantisa != 0)
	{
		g_mode.prec = 0;
		return (ft_strcpy(res, (g_mode.specif == 'f') ? "nan" : "NAN"));
	}
	else if (d1.parts.exponent == 2047 && d1.parts.mantisa == 0)
	{
		g_mode.prec = 0;
		return (ft_strcpy(res, (g_mode.specif == 'f') ? "inf" : "INF"));
	}
	return (res);
}
