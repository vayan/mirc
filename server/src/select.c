/*
** select.c for  in /home/vailla_y/Projet/myirc/svn_my_irc/server/src
**
** Made by yann vaillant
** Login   <vailla_y@epitech.net>
**
** Started on  Sun Apr 22 21:37:07 2012 yann vaillant
** Last update Sun Apr 22 21:41:41 2012 yann vaillant
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <time.h>
#include "server.h"

void		select_list(t_client *all_client, fd_set *readf)
{
  t_client	*tmp;

  tmp = all_client;
  FD_ZERO(readf);
  while (tmp)
    {
      FD_SET(tmp->fd, readf);
      tmp = tmp->next;
    }
}
