/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: videsvau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 05:15:24 by videsvau          #+#    #+#             */
/*   Updated: 2017/11/12 03:10:14 by videsvau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# include <termcap.h>
# include <termios.h>
# include <curses.h>
# include "../libft/includes/libft.h"

typedef struct			s_env
{
	char				*env;
	struct s_env		*next;
}						t_env;

typedef struct			s_inp
{
	char				c;
	int					pos;
	struct s_inp		*next;
	struct s_inp		*previous;
}						t_inp;

typedef struct			s_sh
{
	char				*home_env;
	char				buff[6];
	int					posy;
	int					prompt_len;
	int					pos_at;
	int					width;
	int					retval;
	char				pwd[2048];
	struct s_env		*env;
}						t_sh;

struct termios			g_old_term;
struct termios			g_new_term;

/*						environment										*/

char					*get_specific_env(char *env, t_env **envlist);
void					get_env(char **env, t_sh *sh);
void					env_push_back(t_env **envlist, char *env);
t_env					*new_env(char *env);

/*						pwd_stuff										*/

void					print_prompt(t_sh *sh);
void					tild_prompt(t_sh *sh);
void					prompt_colors(int i);

#endif
