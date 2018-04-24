/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 12:40:56 by oantonen          #+#    #+#             */
/*   Updated: 2018/01/19 12:36:30 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hprintf.h"

int		first_bit(unsigned int c)
{
	int		first;

	first = 31;
	while (first && !((c >> first) & 1U))
		first--;
	return (first + 1);
}

void	pf_lputchar_2byte(unsigned int c, char *ch)
{
	unsigned char	ch2;
	unsigned char	ch1;
	unsigned int	mask2;

	mask2 = 49280;
	ch2 = (c << 26) >> 26;
	ch1 = ((c >> 6) << 27) >> 27;
	ch[0] = (mask2 >> 8) | ch1;
	ch[1] = ((mask2 << 24) >> 24) | ch2;
}

void	pf_lputchar_3byte(unsigned int c, char *ch)
{
	unsigned int	mask3;

	mask3 = 14712960;
	ch[2] = (c << 26) >> 26;
	ch[1] = ((c >> 6) << 26) >> 26;
	ch[0] = ((c >> 12) << 28) >> 28;
	ch[0] = (mask3 >> 16) | ch[0];
	ch[1] = ((mask3 << 16)) >> 24 | ch[1];
	ch[2] = ((mask3 << 24) >> 24) | ch[2];
}

void	pf_lputchar_4byte(unsigned int c, char *ch)
{
	unsigned int	mask4;

	mask4 = 4034953344;
	ch[3] = (c << 26) >> 26;
	ch[2] = ((c >> 6) << 26) >> 26;
	ch[1] = ((c >> 12) << 26) >> 26;
	ch[0] = ((c >> 18) << 29) >> 29;
	ch[0] = (mask4 >> 24) | ch[0];
	ch[1] = ((mask4 << 8) >> 24) | ch[1];
	ch[2] = ((mask4 << 16)) >> 24 | ch[2];
	ch[3] = ((mask4 << 24) >> 24) | ch[3];
}

char	*pf_putchar(unsigned int c)
{
	unsigned char	chr;
	char			*ch;

	chr = (unsigned char)c;
	ch = ft_strnew(4);
	if (chr == 0 && ISL == 0)
		return (ft_flag_width(ch, 1, g_mode.width));
	if (c == 0)
		return (ft_flag_width(ch, 1, g_mode.width));
	if (ISL == 0 || (ISL && MB_CUR_MAX == 1))
		ch[0] = chr;
	else
	{
		if (first_bit(c) <= 7)
			ch[0] = chr;
		else if (first_bit(c) <= 11)
			pf_lputchar_2byte(c, ch);
		else if (first_bit(c) <= 16)
			pf_lputchar_3byte(c, ch);
		else if (first_bit(c) > 16 && first_bit(c) < 31)
			pf_lputchar_4byte(c, ch);
	}
	if (ft_strchr("sS", g_mode.specif))
		return (ch);
	return (ft_flag_width(ch, ft_strlen(ch), g_mode.width));
}
