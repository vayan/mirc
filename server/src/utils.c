/*
** utils.c for  in /home/vailla_y/Projet/myirc/svn_my_irc/server/src
**
** Made by yann vaillant
** Login   <vailla_y@epitech.net>
**
** Started on  Sun Apr 22 21:38:47 2012 yann vaillant
** Last update Sun Apr 22 21:39:57 2012 yann vaillant
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

t_client	*get_client_by_nick(char *nick)
{
  t_client	*all_client;

  all_client = get_all_client(NULL);
  while (all_client)
    {
      if (strcmp(all_client->nick, nick) == 0)
	return (all_client);
      all_client = all_client->next;
    }
  return (NULL);
}

void	aff_word_tab(char **tab)
{
  int	i;

  i = 0;
  while (tab[i])
    {
      printf ("%s\n", tab[i]);
      i++;
    }
}

t_client		*get_all_client(t_client *_all_client)
{
  static t_client	*client = NULL;

  if (_all_client != NULL)
    client = _all_client;
  return (client);
}

int		get_higher_fd(t_client *all_client)
{
  t_client	*tmp;

  tmp = all_client;
  if (tmp == NULL)
    return (3);
  while (tmp->next)
    tmp = tmp->next;
  return (tmp->fd);
}

char	*rand_str(char *dst, int size)
{
  char	text[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  int	i;
  int	len;

  len = rand() % (size - 1);
  for (i = 0; i < len; ++i)
    dst[i] = text[rand() % (sizeof text - 1)];
  dst[i] = '\0';
  return (dst);
}
