/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_splitted_tools.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 12:47:51 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/11 13:46:25 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		is_a_directory(char *str)
{
	ft_putstr("21sh: is a directory: ");
	ft_putstr(str);
}

int			valid_type(int type)
{
	if (type < 1024 && type > 64)
		return (1);
	if (type > 2048 && type < 131072)
		return (1);
	return (0);
}

char		**concat_content(t_inpl **inpl)
{
	int		len;
	t_inpl	*cp;
	char	**cont;

	len = 1;
	cp = (*inpl);
	while (cp && valid_type(cp->type))
	{
		cp->type < 1024 ? len++ : 0;
		cp = cp->next;
	}
	if (!(cont = (char**)malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	len = 0;
	cp = *inpl;
	while (cp && valid_type(cp->type))
	{
		if (cp->type < 1024)
			if (!(cont[len++] = inp_to_cont(&cp->inp)))
				return (NULL);
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

t_redir		*return_last_redir(t_redir **redir)
{
	t_redir	*last;

	last = *redir;
	while (last->next)
		last = last->next;
	return (last);
}
