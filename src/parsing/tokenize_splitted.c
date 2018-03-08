/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_splitted.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 16:33:23 by videsvau          #+#    #+#             */
/*   Updated: 2018/03/08 16:06:16 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

t_tok		*new_tok(int *settings, void *func, char **cont)
{
	t_tok	*ret;

	if (!(ret = (t_tok*)malloc(sizeof(t_tok))))
		return (NULL);
	ret->is_redir = settings[0];
	ret->fd[0] = settings[1];
	ret->fd[1] = settings[2];
	ret->is_cond = settings[3];
	ret->flag = settings[4];
	ret->cont = cont;
	ret->func = func;
	ret->next = NULL;
	ret->previous = NULL;
	return (ret);
}

void		tok_push_back(t_tok **tok, int *settings, void *func, char **cont)
{
	t_tok	*cp;
	t_tok	*add;

	if (!(*tok))
		(*tok) = new_tok(settings, func, cont);
	else
	{
		cp = *tok;
		while (cp->next)
			cp = cp->next;
		add = new_tok(settings, func, cont);
		cp->next = add;
		add->previous = cp;
	}
}

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

int			concat_content(t_inpl **inpl, t_tok **tok, int type)
{
	int		len;
	t_inpl	*cp;
	char	**cont;
	int		settings[5];
	void	*func;

	func = NULL;
	len = 1;
	cp = (*inpl);
	settings[0] = 0;
	settings[3] = 0;
	while (cp && cp->type < 1024 && cp->type > 64)
	{
		len++;
		cp = cp->next;
	}
	if (!(cont = (char**)malloc(sizeof(char*) * (len + 1))))
		return (0);
	len = 0;
	while ((*inpl) && (*inpl)->type < 1024 && (*inpl)->type > 64)
	{
		if (!(cont[len] = inp_to_cont(&(*inpl)->inp)))
			return (0);
		len++;
		(*inpl) = (*inpl)->next;
	}
	cont[len] = NULL;
	if (type & BUILTIN)
		func = get_builtin_function(cont[0]);
	tok_push_back(tok, settings, func, cont);
	if ((*inpl) && (*inpl)->previous)
		(*inpl) = (*inpl)->previous;
	return (1);
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

int			tokenize_splitted(t_inpl **inpl, t_sh *sh, t_tok **tok)
{
	t_inpl	*cp;
	int		settings[5];

	settings[0] = 0;
	if ((cp = (*inpl)))
	{
		sh->posy++;
		while (cp)
		{
			if (cp->type & AND || cp->type & OR || cp->type & PIPE)
			{
				if (valid_condition(&cp))
				{
					if (cp->type & OR || cp->type & AND)
					{
						settings[0] = 0;
						settings[3] = 1;
					}
					else
					{
						settings[0] = 1;
						settings[1] = 1;
						settings[2] = 0;
						settings[3] = 0;
					}
					settings[4] = cp->type;
					tok_push_back(tok, settings, NULL, NULL);
				}
				else
					return ((int)special_error(&cp->inp));
			}
			if (cp->type & TOFILE || cp->type & ATOFILE)
			{
				if ((settings[2] = valid_tofile(&cp)) != -1)
				{
					settings[0] = 1;
					settings[1] = 1;
					tok_push_back(tok, settings, NULL, NULL);
				}
				else
					return ((int)special_error(&cp->inp));
			}
			if (cp->type & TOEXE)
			{
				if ((settings[1] = valid_file(&cp)) != -1)
				{
					ft_putnbr(settings[1]);
					settings[0] = 1;
					settings[2] = 0;
				}
				else
					return ((int)special_error(&cp->inp));
				tok_push_back(tok, settings, NULL, NULL);
			}
			if (cp->type & COMMAND || cp->type & BUILTIN)
				if (!concat_content(&cp, tok, cp->type))
					return (0);
			if (!cp)
				break ;
			cp = cp->next;
		}
	}
	return (1);
}
