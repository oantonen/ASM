/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 12:15:24 by oantonen          #+#    #+#             */
/*   Updated: 2018/03/29 15:43:53 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPLIT_LINE_H
# define SPLIT_LINE_H

typedef struct	s_spl
{
	char	*lbl;
	char	*instr;
	char	q_arg;
	t_list	*args;

}				t_spl;

#endif