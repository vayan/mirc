/*
** send.c for  in /home/vailla_y/Projet/myirc/svn_my_irc/server/src
**
** Made by yann vaillant
** Login   <vailla_y@epitech.net>
**
** Started on  Sun Apr 22 21:37:22 2012 yann vaillant
** Last update Sun Apr 22 21:59:47 2012 yann vaillant
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

int		broadcast_to_one_client(char *msg, t_client *me)
{
  t_client	*tmp;
  char		*full_msg;

  full_msg = xmalloc(MAX_INPUT * sizeof(char*));
  memset(full_msg, 0, MAX_INPUT);
  strcat(full_msg, me->nick);
  strcat(full_msg, " > ");
  strcat(full_msg, msg);
  strcat(full_msg, "\n");
  tmp = me;
  xsend (tmp->fd, full_msg, strlen(full_msg), MSG_DONTWAIT);
  free(full_msg);
  return (0);
}

int		broadcast_to_all_client(t_client *all_client,
				char *msg, char *channel, t_client *me)
{
  t_client	*tmp;
  char		*full_msg;

  if (channel == NULL || msg == NULL)
    return (-1);
  full_msg = xmalloc(MAX_INPUT * sizeof(char*));
  memset(full_msg, 0, MAX_INPUT);
  strcat(full_msg, me->nick);
  strcat(full_msg, " > ");
  strcat(full_msg, msg);
  strcat(full_msg, "\n");
  tmp = all_client;
  while (tmp)
    {
      if ((tmp->channel != NULL) &&
	  (strcmp(tmp->channel, channel) == 0))
	xsend (tmp->fd, full_msg, strlen(full_msg), MSG_DONTWAIT);
      tmp = tmp->next;
    }
  free(full_msg);
  return (0);
}

int		broadcast_to_all_client_but_me(t_client *all_client,
				       char *msg, char *channel, t_client *me)
{
  t_client	*tmp;
  char		*full_msg;

  if (channel == NULL || msg == NULL)
    return (-1);
  full_msg = xmalloc(MAX_INPUT * sizeof(char*));
  memset(full_msg, 0, MAX_INPUT);
  strcat(full_msg, me->nick);
  strcat(full_msg, " > ");
  strcat(full_msg, msg);
  strcat(full_msg, "\n");
  tmp = all_client;
  while (tmp)
    {
      if ((tmp->channel != NULL) &&
	  (strcmp(tmp->channel, channel) == 0) && (tmp->fd != me->fd))
	xsend (tmp->fd, full_msg, strlen(full_msg), MSG_DONTWAIT);
      tmp = tmp->next;
    }
  free(full_msg);
  return (0);
}
