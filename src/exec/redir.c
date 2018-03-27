/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 17:55:11 by jamerlin          #+#    #+#             */
/*   Updated: 2018/03/25 17:55:20 by jamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/header.h"

void    left_redirect(t_listc *cmd, t_pipe *tabTube, int i) //redirection d'un fichier vers une sortie
{
    int ret;
    if (!(ret = open(cmd->redirs->file, O_RDONLY)))
    {
        close(ret);
        errExit(cmd->redirs->file);
    }
    tabTube[i].cote[0] = (cmd->redirs->file) ? ret : cmd->redirs->redir[2];
    tabTube[i].cote[1] = cmd->redirs->redir[0];
}

void right_redirect(t_listc *cmd, t_pipe *tabTube, int i) //redirection d'une sortie vers un fichier
{
    tabTube[i].cote[0] = (cmd->redirs->file) ? open(cmd->redirs->file, O_RDWR| O_TRUNC | O_CREAT, S_IRWXU) 
        : cmd->redirs->redir[2];
    tabTube[i].cote[1] = cmd->redirs->redir[0];
}

void    heredock_redirect(t_listc *cmd, t_pipe *tabTube, int i)
{
    int j;

    j = 0;
    if (pipe(tabTube[i].cote) == -1)
        errExit("pipe");
    while (cmd->redirs->heredoc[j])
    {
        write(tabTube[i].cote[1], cmd->redirs->heredoc[j],ft_strlen(cmd->redirs->heredoc[j]));
        j++;
    }
    close(tabTube[i].cote[1]);
}

void    double_right_redirect(t_listc *cmd, t_pipe *tabTube, int i)// redirection d'une sortie vers la fin d'un fichier
{
    tabTube[i].cote[0] = (cmd->redirs->file) ? open(cmd->redirs->file, O_RDWR | O_APPEND | O_CREAT, S_IRWXU ) : cmd->redirs->redir[2];
    tabTube[i].cote[1] = cmd->redirs->redir[0] ;
}

void    do_aggre(t_listc *cmd, t_pipe *tabTube , int i)
{
    if (cmd->redirs->redir[1] == AGGR)
    {
        if (cmd->redirs->redir[0] != -1 && (cmd->redirs->redir[1] != -1 && cmd->redirs->file == NULL))
        {
            tabTube[i].cote[0] = cmd->redirs->redir[2]; 
            tabTube[i].cote[1] = cmd->redirs->redir[0];
        }
    }
    else if (cmd->redirs->redir[1] == 12288)
    {
        if (cmd->redirs->file != NULL)
        {
            tabTube[i].cote[0] = open(cmd->redirs->file, O_RDWR | O_APPEND | O_CREAT, S_IRWXU);
            tabTube[i].cote[1] = cmd->redirs->redir[0];
        }
        else
        {
            tabTube[i].cote[0] = cmd->redirs->redir[2];
            tabTube[i].cote[1] = cmd->redirs->redir[0];
            //close(tabTube[i].cote[0]);
        }
    }
    else if (cmd->redirs->redir[1] == 28672)
    ;
}

void   redirect(t_listc *cmd, t_pipe *tabTube , int i) // gestion des redirections
{
    int j = 0;
    
    while (cmd->redirs != NULL)
    {
        if (cmd->redirs && cmd->redirs->redir[1] == 0)
            left_redirect(cmd, tabTube, i); // une liste de 1 maillon avec le fichier renseigne 
        else if (cmd->redirs && cmd->redirs->redir[1] == 1)
            right_redirect(cmd, tabTube, i); // une liste de 1 maillon avec le fichier renseigne
        else if (cmd->redirs && cmd->redirs->redir[1] == 3)
            double_right_redirect(cmd, tabTube, i); // une liste de 1 maillon avec le fichier renseigne
        else if (cmd->redirs && (cmd->redirs->redir[1] == AGGR || cmd->redirs->redir[1] == AGGRFILE 
            || cmd->redirs->redir[1] == AGGROUT || cmd->redirs->redir[1] == AGGR + AGGRFILE))
            do_aggre(cmd, tabTube, i); 
       // dprintf(2,"tabTube.cote[0] == [%d] ; tabTube.cote[1] == [%d] ; i == [%d]\n", tabTube[i].cote[0], tabTube[i].cote[1], i/*j**/);
        if (tabTube[i].cote[0] != -1) {
            if (cmd->redirs->redir[1] != 0 && cmd->redirs->redir[1] != 4 && cmd->redirs->redir[0] != 2)
                dup2(tabTube[i].cote[0], STDOUT_FILENO);
            else if (cmd->redirs->redir[0] != 2)
                dup2(tabTube[i].cote[0], STDIN_FILENO);
            else
                dup2(tabTube[i].cote[0], STDERR_FILENO);
        }  
        //dprintf(2, "FD1[%d] -- FD2[%d]\n", tabTube[i].cote[0], tabTube[i].cote[1]);
        if (cmd->redirs && !(cmd->redirs->redir[1] == AGGR || cmd->redirs->redir[1] == AGGRFILE 
            || cmd->redirs->redir[1] == AGGROUT || cmd->redirs->redir[1] == AGGR + AGGRFILE))
            close(tabTube[i].cote[0]);
        cmd->redirs = cmd->redirs->next;
        j++;
    }
    i++;
}
