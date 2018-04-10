/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_updater.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 01:33:43 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/10 16:51:59 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

int			try_update_context(char c, int flag)
{
	if (c == '\'')
	{
		if (flag & QUOTE)
			return (flag - QUOTE);
		else if (!flag)
			return (flag | QUOTE);
	}
	if (c == '\"')
	{
		if (flag & DQUOTE)
			return (flag - DQUOTE);
		else if (!flag)
			return (flag | DQUOTE);
	}
	return (flag);
}

int			update_context(int context, int flag)
{
	if (context & flag)
		return (context - flag);
	return (context | flag);
}

