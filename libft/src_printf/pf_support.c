/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_support.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 17:26:37 by oantonen          #+#    #+#             */
/*   Updated: 2018/01/18 21:21:41 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hprintf.h"

char	*pf_count_written(va_list ap)
{
	uintmax_t	*n;

	n = va_arg(ap, void*);
	*n = g_mode.sup_len;
	g_mode.cur_len = 0;
	return (ft_strnew(0));
}

int		isdigit_spec(char s, int **pos)
{
	char	*dig;
	int		real_pos;

	*pos = &real_pos;
	real_pos = g_mode.sup_len - g_mode.cur_len;
	dig = "123456789";
	while (*dig != s && *dig)
		dig++;
	return ((*dig == s) ? TRUE : FALSE);
}

char	*pf_function_call(char c, va_list ap)
{
	unsigned int ch;

	if (c == 'c' || c == 'C')
	{
		ch = va_arg(ap, unsigned int);
		return (pf_putchar(ch));
	}
	else if (c == 's' || c == 'S')
		return (pf_putstr(ap));
	else if (c == 'd' || c == 'i' || c == 'D')
		return (pf_put_signed_nb(ap));
	else if (c == 'p')
		return (pf_putaddr(ap));
	else if (ft_strchr("oOuUxXb", c))
		return (pf_put_unsigned_nb(ap));
	else if (c == '%')
		return (pf_percent());
	else if (c == 'f' || c == 'F')
		return (pf_put_float_f(ap));
	else if (c == 'n')
		return (pf_count_written(ap));
	return ("op-op");
}

int		specif(char s)
{
	char	*convers;
	char	*ptr;

	convers = "%csnpdouxXCSOiDUfFb";
	ptr = convers;
	if (ft_strchr("CSDOU", s))
	{
		L;
		s = s + 32;
	}
	(s == 'i') ? s = 'd' : s;
	if ((ft_strchr(convers, s)))
		g_mode.specif = s;
	while (*convers)
	{
		if (*convers == s)
			return (convers - ptr);
		convers++;
	}
	return (-1);
}

int		pf_get_num(char **str)
{
	int		res;
	char	symb;

	res = 0;
	symb = **str;
	while (ft_isdigit(**str) && **str)
	{
		res = res * 10 + (symb - 48);
		symb = *(++*str);
	}
	*str = *str - 1;
	return (res);
}
