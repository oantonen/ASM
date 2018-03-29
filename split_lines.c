/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 13:20:44 by oantonen          #+#    #+#             */
/*   Updated: 2018/03/29 20:07:25 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_asm.h"

int 	save_str()

int		token(char c, char *str, int i, t_spl *i_spl)
{
	if (c == LABEL_CHAR && i_spl->lbl == NULL)
		return (1);
	else if (i_spl->lbl && ft_isalpha(c) && !i_spl->instr)
		return (2);
	else if (c == ' ' || c == '\t')
		return (3);
	else if (c == ',')
		return (4);
	return (10);
}

void	split_cur_line(t_list **bgng, t_spl *i_spl, char *str)
{
	int 	i;
	int 	k;
	int 	type;

	i = 0;
	k = 0;
	i_spl = (i_spl*){NULL, NULL, 0, NULL};
	while (str[i])
	{
		type = token(str[i], &str[i], k, i_spl);
		save_str(type, &str[i], *k, i_spl);
		i++;
		k++;
	}

}

void	split_lines(t_fls *file, t_list *instr)
{
	int 	i;
	t_spl	*i_spl;

	i_spl = NULL;
	i = 0;
	while (instr)
	{
		split_cur_line(&i_spl, instr->content);
		instr = instr->next;
	}

}