/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 18:35:16 by oantonen          #+#    #+#             */
/*   Updated: 2018/03/19 22:18:13 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hprintf.h"
#include <locale.h>
#include <limits.h>

void	symbol_flags(char s)
{
	(s == '-') ? MINUS : s;
	(s == '+') ? PLUS : s;
	(s == ' ') ? SPACE : s;
	(s == '#') ? HASH : s;
	(s == '0') ? ZERO : s;
	(s == '\'') ? APOSTROPHE : s;
}

void	length_modifiers(char **s)
{
	if (**s == 'h' && *((*s) + 1) != 'h')
		H;
	if (**s == 'h' && *((*s) + 1) == 'h')
	{
		*s += 1;
		HH;
	}
	(**s == 'l' && *((*s) + 1) != 'l') ? L : **s;
	(**s == 'l' && *((*s) + 1) == 'l') ? LL : **s;
	(**s == 'l' && *((*s) + 1) == 'l') ? *s += 1 : *s;
	(**s == 'j') ? J : **s;
	(**s == 'z') ? Z : **s;
	(**s == 'L') ? LD : **s;
}

char	*all_flags(char *s, va_list ap, char *flags, int **pos)
{
	g_mode.flags = 0;
	g_mode.prec = 0;
	g_mode.width = 0;
	g_mode.specif = 0;
	while (*s && specif(*s) == -1)
	{
		symbol_flags(*s);
		(isdigit_spec(*s, pos) == 1) ? g_mode.width = pf_get_num(&s) : *s;
		(*s == '*') ? g_mode.width = va_arg(ap, int) : *s;
		(g_mode.width < 0) ? MINUS : 0;
		(g_mode.width < 0) ? g_mode.width *= -1 : g_mode.width;
		if (*s == '.')
		{
			DOT;
			(ft_isdigit(*++s)) ? g_mode.prec = pf_get_num(&s) : *s--;
			(*++s == '*') ? g_mode.prec = va_arg(ap, int) : *s--;
		}
		length_modifiers(&s);
		if (*s == '\0' || specif(*s) != -1 || !ft_strchr(flags, *s))
			break ;
		else
			s++;
	}
	return (s);
}

char	*browse_arg(char *arg, va_list ap, char *flags, char *sup_str)
{
	char	*clr;
	int		*position;

	position = NULL;
	while (*arg)
	{
		if (ft_strchr(arg, '%') == NULL)
		{
			ft_memcpy(&sup_str[g_mode.sup_len], arg, ft_strlen(arg));
			g_mode.sup_len += ft_strlen(arg);
			break ;
		}
		ft_memcpy(&sup_str[g_mode.sup_len], arg, ft_strchrlen(arg, '%'));
		g_mode.sup_len += ft_strchrlen(arg, '%');
		arg = ft_strchr(arg, '%');
		arg = all_flags(++arg, ap, flags, &position);
		if (*arg && ft_strchr("%cfFspdouxXCSOiDUnb", *arg) != NULL)
		{
			clr = pf_function_call(*arg, ap);
			isdigit_spec(*arg++, &position);
			ft_memcpy(&sup_str[*position], clr, g_mode.cur_len);
			ft_strdel(&clr);
		}
	}
	return (sup_str);
}

int		ft_printf(const char *arg, ...)
{
	va_list		ap;
	char		*super_str;
	int			printf_len;
	char		*flags;

	super_str = ft_strnew(1000);
	flags = " -+#*hlL$jz\'.01234567890";
	va_start(ap, arg);
	super_str = browse_arg((char*)arg, ap, flags, super_str);
	va_end(ap);
	write(1, super_str, g_mode.sup_len);
	ft_strdel(&super_str);
	printf_len = g_mode.sup_len;
	g_mode.sup_len = 0;
	return (printf_len);
}
