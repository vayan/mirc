/*
** add_client.c for  in /home/vailla_y/Projet/myirc/svn_my_irc/server/src
**
** Made by yann vaillant
** Login   <vailla_y@epitech.net>
**
** Started on  Sun Apr 22 21:28:02 2012 yann vaillant
** Last update Sun Apr 22 21:32:42 2012 yann vaillant
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

t_client	*add_client(t_client *all_client, int fd)
{
  t_client	*tmp;
  t_client	*new;
  char		*nick;
  char		*rd_str;

  srandom(time(NULL));
  nick = xmalloc (255 * sizeof(*nick));
  rd_str = xmalloc (255 * sizeof(*nick));
  memset(nick, 0, 255);
  strcat(nick, "Host");
  strcat(nick, rand_str(rd_str, 10));
  new = xmalloc(sizeof(t_client));
  tmp = all_client;
  new->fd = fd;
  new->channel = NULL;
  new->nick = nick;
  new->next = NULL;
  if (tmp == NULL)
    return (new);
  while (tmp->next)
    tmp = tmp->next;
  tmp->next = new;
  return (NULL);
}

void		aff_all_client(t_client *all_client)
{
  t_client	*tmp;

  tmp = all_client;
  while (tmp)
    {
      printf ("client %d | nick : %s | channel %s \n",
	      tmp->fd, tmp->nick, tmp->channel);
      tmp = tmp->next;
    }
}
