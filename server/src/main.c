/*
** main.c for  in /home/vailla_y/Projet/myirc/svn_my_irc/server/src
**
** Made by yann vaillant
** Login   <vailla_y@epitech.net>
**
** Started on  Sun Apr 22 21:35:17 2012 yann vaillant
** Last update Sun Apr 22 21:36:48 2012 yann vaillant
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
#include <signal.h>
#include "server.h"

void	init_socket(struct sockaddr_in    *sin, char *_port)
{
  int	port;

  port = atoi(_port);
  sin->sin_family = AF_INET;
  sin->sin_port = htons(port);
  sin->sin_addr.s_addr = INADDR_ANY;
}

int	main_loop(int s, socklen_t client_sin_len,
		  struct sockaddr_in client_sin, t_client *all_client)
{
  int	cs;

  while (11)
    {
      fd_set		readf;
      struct	timeval	tv;

      tv.tv_sec = 1;
      tv.tv_usec = 0;
      select_list(all_client, &readf);
      FD_SET(s, &readf);
      if (select(get_higher_fd(all_client) + 1, &readf, NULL, NULL, &tv) == -1)
	printf("Errror : select fail\n");
      if (FD_ISSET(s, &readf))
	{
	  cs = accept(s, (struct sockaddr *)&client_sin, &client_sin_len);
	  if (all_client == NULL)
	    get_all_client(all_client = add_client(all_client, cs));
	  else
	    add_client(all_client, cs);
	  send (cs, "Bienvenue sur YIRC!\n",
		strlen("Bienvenue sur YIRC!\n"), MSG_DONTWAIT);
	}
      get_data_from_client(all_client, &readf);
    }
}

void		clean_quit()
{
  t_client	*all_client;

  all_client = get_all_client(NULL);
  while (all_client)
    {
      xclose(all_client->fd);
      if (all_client->nick != NULL)
	free(all_client->nick);
      if (all_client->channel != NULL)
	free(all_client->channel);
      all_client = all_client->next;
    }
  xclose(3);
  printf("\n");
  exit (11);
}

int			main(int ac, char **av)
{
  int			s;
  struct sockaddr_in	sin;
  struct sockaddr_in	client_sin;
  socklen_t		client_sin_len;
  t_client		*all_client;

  xsignal(SIGINT, clean_quit);
  if (ac != 2)
    return (1);
  all_client = NULL;
  if ((s = socket(PF_INET, SOCK_STREAM, 0)) == -1)
  {
  	perror("scoket");
    return (-1);
  }
  init_socket(&sin, av[1]);
  setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &client_sin, sizeof(client_sin));
  xbind(s, (struct sockaddr*)&sin, sizeof(sin));
  xlisten(s, 42);
  client_sin_len = sizeof(client_sin);
  main_loop(s, client_sin_len, client_sin, all_client);
  xclose(s);
  return (0);
}
