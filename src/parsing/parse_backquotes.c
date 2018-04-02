/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_backquotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 18:59:32 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/02 23:33:24 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		parse_backquotes(t_inp **inp, t_sh *sh)
{
	t_inpl	*splitted;
	t_listc	*tok;

	tok = NULL;
	splitted = NULL;
	sh->context = 0;
	split_line(&splitted, inp, sh);
	if (splitted && convert_splitted(&splitted, sh) &&
			check_special_surrounding(&splitted))
	{
		tokenize_splitted(&splitted, sh, &tok);
		execute_tokens(&tok, sh);
		free_tokens(&tok);
	}
	free_inpl(&splitted);
	free_list_from_beginning(inp);
}
