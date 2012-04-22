/*
** command_list_channel.c for  in /home/vailla_y/Projet/myirc/svn_my_irc/server/src
**
** Made by yann vaillant
** Login   <vailla_y@epitech.net>
**
** Started on  Sun Apr 22 21:41:25 2012 yann vaillant
** Last update Sun Apr 22 21:41:28 2012 yann vaillant
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

int	exist_channel(char **all_channel, char *new)
{
  int	i;

  i = 0;
  while (all_channel[i])
    {
      if (strcmp(all_channel[i], new) == 0)
	return (1);
      i++;
    }
  return (0);
}

char	**fill_tab_channel(t_client *client)
{
  int	i;
  char	**all_channel;

  all_channel = xmalloc(MAX_INPUT * sizeof(char *));
  all_channel[0] = NULL;
  i  = 0;
  while (client)
    {
      if (client->channel != NULL)
	{
	  if (exist_channel(all_channel, client->channel) == 0)
	    {
	      all_channel[i] = client->channel;
	      i++;
	      all_channel[i] = NULL;
	    }
	}
      client = client->next;
    }
  return (all_channel);
}

int	list_channel(t_client *client, t_client *me, char *channel)
{
  char	**all_channel;
  int	i;

  i  = 0;
  all_channel = fill_tab_channel(client);
  if (channel != NULL)
    {
      if (exist_channel(all_channel, channel) != 0)
	broadcast_to_one_client("Oui le channel existe", me);
    }
  else
    {
      broadcast_to_one_client("===Liste des chanel===", me);
      while (all_channel[i])
	{
	  broadcast_to_one_client(all_channel[i], me);
	  i++;
	}
    }
  free(all_channel);
  return (1);
}
