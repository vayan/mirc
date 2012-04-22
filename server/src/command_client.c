/*
** command_client.c for  in /home/vailla_y/Projet/myirc/svn_my_irc/server/src
**
** Made by yann vaillant
** Login   <vailla_y@epitech.net>
**
** Started on  Sun Apr 22 21:28:54 2012 yann vaillant
** Last update Sun Apr 22 21:32:22 2012 yann vaillant
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

int		send_msg(t_client *me, char *messsag, char *dest_nick)
{
  t_client	*dest;
  char		*msg;

  if (dest_nick == NULL || messsag == NULL)
    return (broadcast_to_one_client("Error: /msg _nick_ _messsage_", me));
  if ((dest = get_client_by_nick(dest_nick)) == NULL)
    return (broadcast_to_one_client("Error : nick inconnu", me));
  msg = xmalloc(MAX_INPUT * sizeof(char *));
  memset(msg, 0, MAX_INPUT);
  strcat(msg, "Message de ");
  strcat(msg, me->nick);
  strcat(msg, " : ");
  strcat(msg, messsag);
  broadcast_to_one_client(msg, dest);
  free(msg);
  return (1);
}

int		list_user(t_client *all_client, t_client *me)
{
  broadcast_to_one_client("Liste des utilisateur connecte :", me);
  while (all_client)
    {
      if (all_client->channel != NULL && me->channel != NULL)
	{
	  if (strcmp(all_client->channel, me->channel) == 0)
	    broadcast_to_one_client(all_client->nick, me);
	}
      all_client = all_client->next;
    }
  return (1);
}

int	join_channel(t_client *client, char *channel)
{
  char	*msg;

  if (channel == NULL || channel[0] != '#' || channel[1] == '\0')
    return (broadcast_to_one_client("Error : /join #nomduchannel", client));
  msg = xmalloc(MAX_INPUT * sizeof (char *));
  memset(msg, 0, MAX_INPUT);
  strcat(msg, "Vous avez rejoins ");
  strcat(msg, channel);
  client->channel = strdup(channel);
  broadcast_to_one_client(msg, client);
  memset(msg, 0, MAX_INPUT);
  strcat(msg, client->nick);
  strcat(msg, " a rejoins le channel");
  broadcast_to_all_client_but_me(get_all_client(NULL), msg, channel, client);
  free(msg);
  return (1);
}

int	change_nick(t_client *client, char *new_nick)
{
  char	*msg;
  char	*old_nick;

  if (new_nick == NULL)
    return (broadcast_to_one_client("Error : /nick _nick_", client));
  if (get_client_by_nick(new_nick) != NULL)
    return (broadcast_to_one_client("Error : ce nick existe deja", client));
  old_nick = strdup(client->nick);
  msg = xmalloc(MAX_INPUT * sizeof (char *));
  memset(msg, 0, MAX_INPUT);
  strcat(msg, "Votre nouveau pseudo est ");
  strcat(msg, new_nick);
  client->nick = strdup(new_nick);
  broadcast_to_one_client(msg, client);
  memset(msg, 0, MAX_INPUT);
  strcat(msg, old_nick);
  strcat(msg, " a changer son pseudo en ");
  strcat(msg, new_nick);
  broadcast_to_all_client_but_me(get_all_client(NULL), msg,
				 client->channel, client);
  free(msg);
  return (1);
}

int	leave_channel(t_client *client)
{
  char	*msg;

  if (client->channel == NULL)
    return (broadcast_to_one_client("Error : vous n'etes dans aucun channel",
				    client));
  msg = xmalloc(MAX_INPUT * sizeof (char *));
  memset(msg, 0, MAX_INPUT);
  strcat(msg, "Vous avez quitter le channel ");
  strcat(msg, client->channel);
  broadcast_to_one_client(msg, client);
  memset(msg, 0, MAX_INPUT);
  strcat(msg, client->nick);
  strcat(msg, " a quitter le channel");
  broadcast_to_all_client_but_me(get_all_client(NULL), msg,
				 client->channel, client);
  client->channel = NULL;
  free(msg);
  return (1);
}
