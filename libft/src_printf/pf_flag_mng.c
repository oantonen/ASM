/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_flag_mng.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:09:36 by oantonen          #+#    #+#             */
/*   Updated: 2018/01/24 13:13:02 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hprintf.h"

char	*pf_apply_flags_nominus(char *s, int len_old, int len_new, char *pref)
{
	char	*new_s;
	int		p;

	p = ft_strlen(pref);
	new_s = ft_strnew(len_new);
	if (g_mode.width > len_old)
		ft_memset(new_s, 32, len_new - len_old);
	if (g_mode.width > len_old && ISZERO == 1 && ISDOT == 0)
		ft_memset(new_s, 48, len_new - len_old);
	else if (g_mode.width > len_old && ISZERO && ft_strchr("fF", g_mode.specif))
		ft_memset(new_s, 48, len_new - len_old);
	else if (g_mode.width > len_old && ISZERO == 1 && g_mode.prec < 0)
		ft_memset(new_s, 48, len_new - len_old);
	if (g_mode.width >= len_old && !ISZERO && *pref)
		ft_strncpy(&new_s[len_new - len_old - p], pref, p);
	else if ((g_mode.width >= len_old && ISZERO && *pref) || \
		g_mode.width < len_old)
		ft_strncpy(new_s, pref, p);
	else if (len_old == 0 && *pref)
		ft_strcpy(new_s, pref);
	ft_strcat(new_s, s);
	g_mode.sup_len += ft_strlen(new_s);
	g_mode.cur_len = ft_strlen(new_s);
	return (new_s);
}

char	*pf_apply_flags(char *s, int len_old, int len_new, char *pref)
{
	char	*new_s;
	int		p;

	p = ft_strlen(pref);
	if (ISMINUS == 1)
	{
		new_s = ft_strnew(len_new);
		ft_strcpy(new_s, pref);
		ft_strcat(new_s, s);
		if (g_mode.width > len_old && *pref)
			ft_memset(&new_s[len_old + p], 32, len_new - len_old - p);
		else if (g_mode.width > len_old && !(*pref))
			ft_memset(&new_s[len_old], 32, len_new - len_old);
		g_mode.sup_len += ft_strlen(new_s);
		g_mode.cur_len = ft_strlen(new_s);
	}
	else
		new_s = pf_apply_flags_nominus(s, len_old, len_new, pref);
	return (new_s);
}

char	*pf_final_modify(char *s, int len_old, int width, char *pref)
{
	int		len_new;
	char	*new_s;

	len_new = 0;
	(width < 0) ? MINUS : width;
	(width < 0) ? width *= -1 : width;
	if (ISHASH && ft_strchr("pxX", g_mode.specif) && width - len_old == 1 && *s)
		len_new += (width - len_old > 2 && *s) ? 2 : width - len_old;
	if (width > len_old && width >= g_mode.prec)
		len_new += width;
	else if (g_mode.prec > len_old && width <= g_mode.prec)
		len_new += g_mode.prec;
	else if (width <= len_old && len_old >= g_mode.prec)
		len_new += len_old;
	if (width <= len_old)
		len_new += ft_strlen(pref);
	new_s = pf_apply_flags(s, len_old, len_new, pref);
	ft_strdel(&s);
	return (new_s);
}
