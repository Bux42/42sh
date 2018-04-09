/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_redir_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 12:09:56 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/09 16:08:51 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void		redir_debug(char *file, int redir_type[3])
{
	ft_putstr("[FILE: ");
	if (file)
		ft_putstr(file);
	else
		ft_putstr("NULL");
	ft_putstr("] [REDIR TYPE:");
	ft_putnbr(redir_type[1]);
	ft_putstr(" FD1:");
	ft_putnbr(redir_type[0]);
	ft_putstr(" FD2:");
	ft_putnbr(redir_type[2]);
	ft_putstr("] ");
}

void		add_laggr_redir(int redir_type[3], t_inpl **inpl, int type)
{
	redir_type[1] = type;
	if (type & LAGGRIN)
		redir_type[2] = -1;
	else
	{
		if ((*inpl)->inp->c == '<')
			redir_type[2] = (*inpl)->inp->next->next->c - 48;
		else
			redir_type[2] = (*inpl)->inp->next->next->next->c - 48;
	}
	if ((*inpl)->inp->c == '<')
		redir_type[0] = 0;
	else
		redir_type[0] = (*inpl)->inp->c - 48;
}

char		*add_aggr_redir(int redir_type[3], t_inpl **inpl, int type)
{
	char	*file;

	file = NULL;
	redir_type[1] = type;
	if ((*inpl)->inp->c == '>')
	{
		redir_type[0] = 1;
		if (!(type & CLOSEAGGR))
			redir_type[2] = (*inpl)->inp->next->next->c - 48;
	}
	else
	{
		redir_type[0] = (*inpl)->inp->c - 48;
		if (!(type & CLOSEAGGR))
			redir_type[2] = (*inpl)->inp->next->next->next->c - 48;
	}
	if (type & CLOSEAGGR)
		redir_type[2] = -1;
	return (file);
}

char		**add_here_redir(int redir_type[3], t_inp **eof)
{
	char	**here;

	here = NULL;
	redir_type[0] = -1;
	redir_type[1] = HEREDOC;
	redir_type[2] = -1;
	here = get_heredoc(eof);
	return (here);
}

char		*add_file_redir(int redir_type[3], t_inp **file, int type)
{
	char	*ret;

	ret = NULL;
	ret = get_file_name(file);
	if (type & TOFILE)
		redir_type[1] = OUT;
	else if (type & ATOFILE)
		redir_type[1] = AOUT;
	else
		redir_type[1] = IN;
	redir_type[0] = 1;
	redir_type[2] = 0;
	return (ret);
}
