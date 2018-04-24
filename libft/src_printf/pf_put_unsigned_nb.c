/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_put_unsigned_nb.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 19:59:35 by oantonen          #+#    #+#             */
/*   Updated: 2018/01/24 13:12:50 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hprintf.h"

/*
** Counting the amount of digits in argument and adding 'apostrophe', '0x/0X',
** '0', filling with zeroes
*/

char		*pf_char_count(uintmax_t value, int base, int *chars, int prec)
{
	int				i;
	uintmax_t		value2;
	char			*fresh;

	i = (value == 0 && ISDOT == 0) ? 1 : 0;
	i = (value == 0 && ISDOT == 0 && ISHASH && g_mode.specif == 'o') ? 0 : i;
	value2 = value;
	while (value)
	{
		value = value / base;
		i++;
	}
	value = value2;
	*chars = i;
	if (MB_CUR_MAX == 4 && ISAPOSTROPHE)
	{
		*chars += (g_mode.specif == 'u' && (i > 3 && value > 0)) ? (i / 3) : 0;
		*chars = (i % 3 == 0 && i > 3) ? *chars - 1 : *chars;
	}
	*chars += (g_mode.specif == 'b' && (i > 4 && value > 0)) ? (i / 4) : 0;
	*chars -= (i % 4 == 0 && i > 4 && g_mode.specif == 'b') ? 1 : 0;
	*chars += (ISHASH && g_mode.specif == 'o' && prec <= i) ? 1 : 0;
	*chars += (prec > *chars) ? prec - *chars : 0;
	fresh = ft_strnew(*chars);
	return (ft_memset(fresh, '0', *chars));
}

char		*pf_itoa_unsigned(uintmax_t value, char c)
{
	int		chars;
	char	*fresh;
	int		base;
	int		i;

	i = -1;
	base = (c == 'o') ? 8 : 0;
	base = (c == 'x' || c == 'X') ? 16 : base;
	base = (c == 'u') ? 10 : base;
	base = (c == 'b') ? 2 : base;
	fresh = pf_char_count(value, base, &chars, g_mode.prec);
	while (value != 0)
	{
		if (++i != 0 && ISAPOSTROPHE && !(i % 3) && c == 'u' && MB_CUR_MAX == 4)
			fresh[--chars] = ',';
		if (i != 0 && !(i % 4) && c == 'b')
			fresh[--chars] = ' ';
		fresh[chars - 1] = (value % base) + ((value % base > 9) ? 87 : '0');
		if (c == 'X')
			fresh[chars - 1] = (value % base) + ((value % base > 9) ? 55 : '0');
		value = value / base;
		chars--;
	}
	return (fresh);
}

uintmax_t	cast_usize(uintmax_t nb)
{
	if (ISHH == 1 && !((g_mode.flags << 20) >> 27))
		return ((unsigned char)nb);
	else if (ISH == 1 && !((g_mode.flags << 20) >> 28))
		return ((unsigned short)nb);
	else if (ISL == 1 && !((g_mode.flags << 20) >> 29))
		return ((unsigned long)nb);
	else if (ISLL == 1 && !((g_mode.flags << 20) >> 30))
		return ((unsigned long long)nb);
	else if (ISJ == 1 && !((g_mode.flags << 20) >> 31))
		return ((uintmax_t)nb);
	else if (ISZ)
		return ((size_t)nb);
	return ((unsigned int)nb);
}

char		*pf_put_unsigned_nb(va_list ap)
{
	char		*s;
	char		*pref;
	int			len_old;
	uintmax_t	arg;

	arg = va_arg(ap, uintmax_t);
	if (ISDOT && ISZERO && g_mode.prec >= 0)
		g_mode.flags &= ~(1UL << 4);
	if (cast_usize(arg) == 0 && g_mode.specif != 'o')
		g_mode.flags &= ~(1UL << 3);
	s = pf_itoa_unsigned(cast_usize(arg), g_mode.specif);
	len_old = ft_strlen(s);
	pref = (g_mode.specif == 'x' && ISHASH && cast_usize(arg)) ? "0x" : "";
	pref = (g_mode.specif == 'X' && ISHASH && cast_usize(arg)) ? "0X" : pref;
	return (pf_final_modify(s, len_old, g_mode.width, pref));
}
