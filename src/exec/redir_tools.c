#include "../../inc/header.h"

void errExit(char *str)
{
    ft_putstr("[");
    ft_putstr(str);
    ft_putstr("]\n");
    exit(1);
}

void    prepare_pipe(t_listc *cmd)
{
    t_listc *cpy;
    int nb_cmd;
    int i;

    cpy = cmd;
    nb_cmd = 0;
    i = 0;
    while (cpy->sep_type == PIPE) 
    {
        if (cpy->sep_type == PIPE)
            nb_cmd++;
        cpy = cpy->next;
    }
    cpy = cmd;
    nb_cmd++;
    while (cpy && i < nb_cmd)
    {
        cpy->nb_arg = nb_cmd;
        i++;
        //cpy->prev = cpy;
		cpy = cpy->next;
    }
}

void	fermeture(int fils, int nb_tube, t_pipe *tabTube)
{
	int i;

	i = 0;
	//fprintf(stderr, "fermeture tubes processus(%d)\n", fils);
	while (i < nb_tube)
	{
		//fprintf(stderr, "\ti = [%d] && fd[0] = [%d]\n", i, tabTube[i].cote[0]);
		//fprintf(stderr, "\ti = [%d] && fd[1] = [%d]\n", i, tabTube[i].cote[1]);
		if (i != (fils - 1)) {
			//fprintf(stderr, "\tfermeture(%d) %d.lire fd[%d]\n", fils, i, tabTube[i].cote[0]);
			close(tabTube[i].cote[0]);
		}
		if (i != fils) {
			//fprintf(stderr, "\tfermeture(%d) %d.ecrire fd[%d]\n", fils, i, tabTube[i].cote[1]);
			close(tabTube[i].cote[1]);
		}
		i++;
	}
}