/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_splitted_tools.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 12:47:51 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/08 12:49:50 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		is_a_directory(char *str)
{
	ft_putstr("21sh: is a directory: ");
	ft_putstr(str);
}

char		**concat_content(t_inpl **inpl)
{
	int		len;
	t_inpl	*cp;
	char	**cont;

	len = 1;
	cp = (*inpl);
	while (cp && cp->type < 1024 && cp->type > 64)
	{
		len++;
		cp = cp->next;
	}
	if (!(cont = (char**)malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	len = 0;
	cp = *inpl;
	while (cp && cp->type < 1024 && cp->type > 64)
	{
		if (!(cont[len] = inp_to_cont(&cp->inp)))
			return (NULL);
		len++;
		cp = cp->next;
	}
	cont[len] = NULL;
	return (cont);
}

char		*get_file_name(t_inp **inp)
{
	char	*ret;
	int		len;
	t_inp	*cp;

	len = 0;
	ret = NULL;
	if ((cp = (*inp)))
	{
		while (cp)
		{
			len++;
			cp = cp->next;
		}
		if (!(ret = (char*)malloc(sizeof(char) * (len + 1))))
			return (NULL);
		ret[len] = '\0';
		cp = *inp;
		len = 0;
		while (cp)
		{
			ret[len++] = cp->c;
			cp = cp->next;
		}
	}
	return (ret);
}
