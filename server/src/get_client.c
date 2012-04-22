/*
** get_client.c for  in /home/vailla_y/Projet/myirc/svn_my_irc/server/src
** 
** Made by yann vaillant
** Login   <vailla_y@epitech.net>
** 
** Started on  Sun Apr 22 21:36:54 2012 yann vaillant
** Last update Sun Apr 22 21:36:55 2012 yann vaillant
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

int	get_cmd_client(t_client *client, char *msg)
{
  char	*tok;
  char	*tok2;

  tok = strtok(msg, " ");
  while (tok != NULL)
    {
      if (strcmp(tok, "join") == 0)
	return (join_channel(client, tok = strtok(NULL, " ")));
      if (strcmp(tok, "nick") == 0)
	return (change_nick(client, tok = strtok(NULL, " ")));
      if (strcmp(tok, "list") == 0)
	return (list_channel(get_all_client(NULL),
			     client, tok = strtok(NULL, " ")));
      if (strcmp(tok, "part") == 0)
	return (leave_channel(client));
      if (strcmp(tok, "users") == 0)
	return (list_user(get_all_client(NULL), client));
      if (strcmp(tok, "msg") == 0)
	return (send_msg(client, tok = strtok(NULL, " "),
			 tok2 = strtok(NULL, " ")));
      tok = strtok(NULL, " ");
    }
  broadcast_to_one_client("Error : command inconnu", client);
  return (0);
}

int		remove_client(t_client *to_remove)
{
  t_client	*tmp;

  xclose(to_remove->fd);
  tmp = get_all_client(NULL);
  if (tmp->fd == to_remove->fd)
    {
      tmp->fd = -1;
      tmp->nick = strdup("");
      tmp->channel = strdup("");
      return (0);
    }
  while (tmp)
    {
      if (tmp->next != NULL)
	{
	  if (tmp->next->fd == to_remove->fd)
	    tmp->next = tmp->next->next;
	}
      tmp = tmp->next;
    }
  if (to_remove->channel != NULL)
    free(to_remove->channel);
  if (to_remove->nick != NULL)
    free(to_remove->nick);
  return (1);
}

void		get_data_from_client(t_client *all_client, fd_set *readfs)
{
  t_client	*tmp;
  char		msg[MAX_INPUT];
  int		ret;

  memset(msg, 0, MAX_INPUT);
  tmp = all_client;
  while (tmp)
    {
      if (FD_ISSET(tmp->fd, readfs))
	{
	  if ((ret = recv(tmp->fd, msg, MAX_INPUT, MSG_DONTWAIT)) != 0)
	    {
	      if (msg[strlen(msg) - 1] == '\n')
		msg[strlen(msg) - 1] = 0;
	      if (tmp->channel != NULL && msg[0] != '/')
		broadcast_to_all_client(all_client, msg, tmp->channel, tmp);
	      else if (msg[0] == '/')
		get_cmd_client(tmp, &msg[1]);
	    }
	  if (ret == 0)
	    remove_client(tmp);
	}
      tmp = tmp->next;
    }
}
