/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_splitted.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 16:33:23 by videsvau          #+#    #+#             */
/*   Updated: 2018/04/02 23:22:49 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

int			valid_condition(t_inpl **inpl)
{
	if ((*inpl)->previous && (*inpl)->next)
	{
		if ((*inpl)->previous->type < 128)
			return (0);
		if ((*inpl)->next->type < 128)
			return (0);
		if ((*inpl)->previous->type & SEMICOLON)
			return (0);
		if ((*inpl)->next->type & SEMICOLON)
			return (0);
		return (1);
	}
	return (0);
}

void		is_a_directory(char *str)
{
	ft_putstr("21sh: is a directory: ");
	ft_putstr(str);
}

int			valid_tofile(t_inpl **inpl)
{
	if ((*inpl)->previous && (*inpl)->next)
	{
		if ((*inpl)->previous->type < 128)
			return (-1);
		if ((*inpl)->previous->type == 2048 || (*inpl)->next->type == 2048)
			return (-1);
	}
	return (1);
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

int			valid_file(t_inpl **inpl)
{
	int		fd;

	fd = -1;
	if ((*inpl)->previous && (*inpl)->next)
	{
		if ((*inpl)->previous->type == 2048)
			return (-1);
		if ((*inpl)->next->type == 2048)
			return (-1);
		if ((*inpl)->previous && (*inpl)->previous->type > 64 && (*inpl)->previous->type < 1024)
			if ((*inpl)->next->type & _FILE)
				return (1);
	}
	else
		return (-1);
	return (fd);
}

t_listc		*new_token(void)
{
	t_listc		*ret;

	if (!(ret = (t_listc*)malloc(sizeof(t_listc))))
		return (NULL);
	ret->func = NULL;
	ret->cont = NULL;
	ret->redirs = NULL;
	ret->prev = NULL;
	ret->next = NULL;
	ret->sep_type = 0;
	ret->nb_arg = 0;
	return (ret);
}

void		tok_push_back(t_listc **tok, t_listc *add)
{
	t_listc		*last;

	if (!*tok)
		*tok = add;
	else
	{
		last = *tok;
		while (last->next)
			last = last->next;
		add->prev = last;
		last->next = add;
	}
}

int			keep_going(int type)
{
	if (type & SEMICOLON)
		return (0);
	if (type & BUILTIN)
		return (0);
	if (type & COMMAND)
		return (0);
	return (1);
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
	{
		file = get_file_name(&(*inpl)->next->inp);
		if (type & TOFILE)
			redir_type[1] = OUT;
		else if (type & ATOFILE)
			redir_type[1] = AOUT;
		else
			redir_type[1] = IN;
		redir_type[0] = 1;
		redir_type[2] = 0;
	}
	else if (type & HERE)
	{
		redir_type[0] = -1;
		redir_type[1] = HEREDOC;
		redir_type[2] = -1;
		here = get_heredoc(&(*inpl)->next->inp);
	}
	else if (type & AGGR)
	{
		redir_type[1] = type;
		if (type & AGGRFILE)
		{
			file = get_file_name(&(*inpl)->next->inp);
			if (ft_strcmp(file, "-") == 0)
			{
				free(file);
				file = NULL;
				redir_type[2] = -1;
			}
		}
		else if (type & AGGROUT)
			redir_type[2] = (*inpl)->inp->next->next->c - 48;
		else
			redir_type[2] = (*inpl)->inp->next->next->next->c - 48;
		if (type & AGGROUT)
			redir_type[0] = 1;
		else
			redir_type[0] = (*inpl)->inp->c - 48;
	}
	else if (type & LAGGR || type & LAGGRIN)
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
	if (!*redir)
		*redir = new_redir(redir_type, file, here);
	else
	{
		last = *redir;
		while (last->next)
			last = last->next;
		last->next = new_redir(redir_type, file, here);
	}
	if (DEBUG)
	{
		ft_putstr("[FILE: ");
		if (file)
			ft_putstr(file);
		else
			ft_putstr("NULL");
		ft_putchar(']');
		ft_putstr(" [REDIR TYPE:");ft_putnbr(redir_type[1]);
		ft_putstr(" FD1:");ft_putnbr(redir_type[0]);
		ft_putstr(" FD2:");ft_putnbr(redir_type[2]);
		ft_putstr("] ");
	}
}

int			is_redirection(int type)
{
	if (type & TOFILE)
		return (1);
	if (type & ATOFILE)
		return (1);
	if (type & TOEXE)
		return (1);
	if (type & HERE)
		return (1);
	if (type & AGGR)
		return (1);
	if (type & AGGRFILE)
		return (1);
	if (type & LAGGR)
		return (1);
	if (type & LAGGRIN)
		return (1);
	return (0);
}

void		add_listc_token(t_inpl **inpl, t_listc **tok, int type)
{
	t_listc	*add;
	t_inpl	*cp;

	type++;
	if ((add = new_token()))
	{
		if (DEBUG)
			custom_return();
		add->cont = concat_content(inpl);
		if (DEBUG)
			ft_putstr(add->cont[0]);
		add->func = get_builtin_function(add->cont[0]);
		if (DEBUG)
		{
			ft_putstr(" is a ");
			if (add->func)
				ft_putstr("builtin ");
			else
				ft_putstr("command ");
		}
		cp = *inpl;
		while (cp->next && keep_going(cp->next->type))
		{
			if (is_redirection(cp->next->type))
				redir_push_back(&add->redirs, &cp->next, cp->next->type);
			if (cp->next->type & PIPE || cp->next->type & AND || cp->next->type & OR || cp->next->type & SEMICOLON)
			{
				add->sep_type = cp->next->type;
				if (DEBUG)
					ft_putnbr(add->sep_type);
				return ((void)tok_push_back(tok, add));
			}
			cp = cp->next;
		}
		add->sep_type = 0;
		if (DEBUG)
			ft_putnbr(add->sep_type);
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
				add_listc_token(&cp, tok, cp->type);
				if (DEBUG)
					ft_putstr(" <= SEP_TYPE");
			}
			cp = cp->next;
		}
	}
	return (1);
}
