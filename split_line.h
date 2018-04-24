/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 12:15:24 by oantonen          #+#    #+#             */
/*   Updated: 2018/04/23 21:33:33 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPLIT_LINE_H
# define SPLIT_LINE_H

typedef struct	s_spl
{
	char	*lbl;
	char	*op_code;
	char	q_arg;
	int 	ln_nb;
	t_list	*args;

}				t_spl;

#endif