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
    tabTube[i].cote[1] = /*(i == 0) ?*/ cmd->redirs->redir[0] /*: tabTube[i].cote[1]*/;
}

void right_redirect(t_listc *cmd, t_pipe *tabTube, int i) //redirection d'une sortie vers un fichier
{
    tabTube[i].cote[0] = (cmd->redirs->file) ? open(cmd->redirs->file, O_RDWR| O_TRUNC | O_CREAT, S_IRWXU) 
    : cmd->redirs->redir[2];
    tabTube[i].cote[1] = /*(i == 0) ?*/ cmd->redirs->redir[0] /*: tabTube[i].cote[1]*/;
}

void    double_right_redirect(t_listc *cmd, t_pipe *tabTube, int i)// redirection d'une sortie vers la fin d'un fichier
{
    tabTube[i].cote[0] = (cmd->redirs->file) ? open(cmd->redirs->file, O_RDWR | O_APPEND | O_CREAT, S_IRWXU ) : cmd->redirs->redir[2];
    tabTube[i].cote[1] = /*(i == 0) ? */cmd->redirs->redir[0] /*: tabTube[i].cote[1]*/;
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
       //dprintf(2,"tabTube.cote[0] == [%d] ; tabTube.cote[1] == [%d] ; i == [%d]\n", tabTube[i].cote[0], tabTube[i].cote[1], i/*j**/);
        
        if (cmd->redirs->redir[1] != 0)
            dup2(tabTube[i].cote[0], STDOUT_FILENO);
        else 
            dup2(tabTube[i].cote[0], STDIN_FILENO);
        close(tabTube[i].cote[0]);
        cmd->redirs = cmd->redirs->next;
        j++;
    }
    i++;
}