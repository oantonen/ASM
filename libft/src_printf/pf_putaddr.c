/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putaddr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/23 14:23:21 by oantonen          #+#    #+#             */
/*   Updated: 2018/01/18 22:30:40 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hprintf.h"

char	*pf_itoa_addr(char *res, uintmax_t value, int count, char *pref)
{
	char		*base_num;
	int			base;

	base = 16;
	base_num = "0123456789abcdef";
	while (value != 0)
	{
		if (value % base > 9)
			res[count - 1] = base_num[value % base];
		else
			res[count - 1] = value % base + '0';
		value = value / base;
		count--;
	}
	return (pf_final_modify(res, ft_strlen(res), g_mode.width, pref));
}

char	*pf_putaddr(va_list ap)
{
	char		*res;
	int			count;
	uintmax_t	adr;
	char		*pref;

	adr = va_arg(ap, uintmax_t);
	pref = "0x";
	HASH;
	res = pf_char_count(adr, 16, &count, g_mode.prec);
	return (pf_itoa_addr(res, adr, count, pref));
}
