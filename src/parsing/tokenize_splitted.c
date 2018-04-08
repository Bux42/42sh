/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_splitted.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 16:33:23 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/08 12:33:49 by videsvau         ###   ########.fr       */
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

t_redir		*new_redir(int *redir_type, char *file, char **here)
{
	t_redir	*redir;

	if (!(redir = (t_redir*)malloc(sizeof(t_redir))))
		return (NULL);
	redir->file = file;
	redir->redir[0] = redir_type[0];
	redir->redir[1] = redir_type[1];
	redir->redir[2] = redir_type[2];
	redir->heredoc = here;
	redir->next = NULL;
	return (redir);
}

void		redir_push_back(t_redir **redir, t_inpl **inpl, int type)
{
	char	*file;
	int		redir_type[3];
	t_redir	*last;
	char	**here;

	here = NULL;
	file = NULL;
	if (type & TOFILE || type & ATOFILE || type & TOEXE)
		file = add_file_redir(redir_type, &(*inpl)->next->inp, type);
	else if (type & HERE)
		here = add_here_redir(redir_type, &(*inpl)->next->inp);
	else if (type & AGGR)
		file = add_aggr_redir(redir_type, inpl, type);
	else if (type & LAGGR || type & LAGGRIN)
		add_laggr_redir(redir_type, inpl, type);
	if (!*redir)
		*redir = new_redir(redir_type, file, here);
	else
	{
		last = *redir;
		while (last->next)
			last = last->next;
		last->next = new_redir(redir_type, file, here);
	}
	redir_debug(file, redir_type);
}

void		add_listc_token(t_inpl **inpl, t_listc **tok)
{
	t_listc	*add;
	t_inpl	*cp;

	if ((add = new_token()))
	{
		add->cont = concat_content(inpl);
		add->func = get_builtin_function(add->cont[0]);
		cp = *inpl;
		while (cp->next && keep_going(cp->next->type))
		{
			if (is_redirection(cp->next->type))
				redir_push_back(&add->redirs, &cp->next, cp->next->type);
			if (cp->next->type & PIPE || cp->next->type & AND ||
					cp->next->type & OR || cp->next->type & SEMICOLON)
			{
				add->sep_type = cp->next->type;
				if (DEBUG)
					ft_putnbr(add->sep_type);
				return ((void)tok_push_back(tok, add));
			}
			cp = cp->next;
		}
		add->sep_type = 0;
		tok_push_back(tok, add);
	}
}

int			tokenize_splitted(t_inpl **inpl, t_sh *sh, t_listc **tok)
{
	t_inpl	*cp;

	if ((cp = (*inpl)))
	{
		sh->posy++;
		while (cp)
		{
			if (cp->type & BUILTIN || cp->type & COMMAND)
			{
				add_listc_token(&cp, tok);
				if (DEBUG)
				{
					ft_putstr(" <= SEP_TYPE");
					custom_return();
				}
			}
			cp = cp->next;
		}
	}
	return (1);
}
