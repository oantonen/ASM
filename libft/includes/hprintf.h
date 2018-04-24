/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hprintf.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 18:38:06 by oantonen          #+#    #+#             */
/*   Updated: 2018/04/19 15:07:10 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HPRINTF_H
# define HPRINTF_H

# include <stdarg.h>
# include "libft.h"
# include "get_next_line.h"
# include <float.h>

typedef struct			s_spec
{
	unsigned int		flags;
	int					width;
	int					prec;
	char				specif;
	int					cur_len;
	int					sup_len;

}						t_spec;

typedef union			u_float_cast
{
	double				f;
	struct
	{
		unsigned long	mantisa : 52;
		unsigned long	exponent : 11;
		unsigned long	sign : 1;
	}					parts;
}						t_float_cast;

t_spec	g_mode;

# define TRUE 1
# define FALSE 0
# define MINUS g_mode.flags |= 1UL << 0
# define PLUS g_mode.flags  |= 1UL << 1
# define SPACE g_mode.flags |= 1UL << 2
# define HASH g_mode.flags |= 1UL << 3
# define ZERO g_mode.flags |= 1UL << 4
# define DOT g_mode.flags |= 1UL << 5
# define HH g_mode.flags |= 1UL << 6
# define H g_mode.flags |= 1UL << 7
# define L g_mode.flags |= 1UL << 8
# define LL g_mode.flags |= 1UL << 9
# define J g_mode.flags |= 1UL << 10
# define Z g_mode.flags |= 1UL << 11
# define APOSTROPHE g_mode.flags |= 1UL << 12
# define LD g_mode.flags |= 1UL << 13
# define C0 g_mode.flags |= 1UL << 14

# define ISMINUS ((g_mode.flags >> 0) & 1U)
# define ISPLUS ((g_mode.flags >> 1) & 1U)
# define ISSPACE ((g_mode.flags >> 2) & 1U)
# define ISHASH ((g_mode.flags >> 3) & 1U)
# define ISZERO ((g_mode.flags >> 4) & 1U)
# define ISDOT ((g_mode.flags >> 5) & 1U)
# define ISHH ((g_mode.flags >> 6) & 1U)
# define ISH ((g_mode.flags >> 7) & 1U)
# define ISL ((g_mode.flags >> 8) & 1U)
# define ISLL ((g_mode.flags >> 9) & 1U)
# define ISJ ((g_mode.flags >> 10) & 1U)
# define ISZ ((g_mode.flags >> 11) & 1U)
# define ISAPOSTROPHE ((g_mode.flags >> 12) & 1U)
# define ISLD ((g_mode.flags >> 13) & 1U)
# define ISC0 ((g_mode.flags >> 14) & 1U)

char					*pf_putchar(unsigned int c);
char					*pf_putstr(va_list ap);
char					*pf_putaddr(va_list ap);
char					*ft_flag_width(char *str, int len, int width);
char					*pf_put_signed_nb(va_list ap);
char					*pf_put_unsigned_nb(va_list ap);
int						specif(char s);
char					*add_mem(char *super_str, char *result, int *buf);
int						pf_get_num(char **str);
char					*pf_put_float_f(va_list ap);
void					pf_float_output(char **s, int len, int bl, int sign);
double					pf_float_sqrt(long double sample, int prec);
char					*pf_final_modify(char *s, int len_old, int width,\
	char *pref);
char					*pf_percent();
char					*pf_function_call(char c, va_list ap);
char					*pf_char_count(uintmax_t value, int base, int *chars,\
	int prec);
char					*pf_float_inf_nan(t_float_cast d1);
int						pf_check_even(long double nb);
int						isdigit_spec(char s, int **pos);
int						ft_printf(const char *arg, ...);

#endif
