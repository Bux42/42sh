/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 09:43:42 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/08 09:46:57 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

int			special_tok(char c)
{
	if (c == '>')
		return (1);
	if (c == '<')
		return (1);
	if (c == '|')
		return (1);
	if (c == '&')
		return (1);
	if (c == ';')
		return (1);
	return (0);
}

int			ending_special_char(char c)
{
	if (c == ' ' || c == '\t' || c == '\'' || c == '\"' || c == '`')
		return (1);
	if (c < 123 && c > 96)
		return (1);
	if (c < 96 && c > 64)
		return (1);
	if (c < 48 && c > 44)
		return (1);
	return (0);
}

int			right_context(int flag)
{
	if (flag & QUOTE)
		return (0);
	if (flag & DQUOTE)
		return (0);
	return (1);
}

int			check_quoting(char c)
{
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (1);
	if (c == '`')
		return (1);
	return (0);
}

int			ending_char(char c)
{
	if (c == ' ')
		return (1);
	if (c == '\t')
		return (1);
	if (c == '|')
		return (1);
	if (c == '&')
		return (1);
	if (c == '>')
		return (1);
	if (c == '<')
		return (1);
	if (c == ';')
		return (1);
	return (0);
}
