/*
** xother.c for  in /home/vailla_y/Projet/myirc/svn_my_irc/server/src
**
** Made by yann vaillant
** Login   <vailla_y@epitech.net>
**
** Started on  Sun Apr 22 22:23:01 2012 yann vaillant
** Last update Sun Apr 22 22:25:35 2012 yann vaillant
*/

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "server.h"

int	xlisten(int sockfd, int backlog)
{
  int	ret;

  if ((ret = listen(sockfd, backlog)) == -1)
    {
      perror("listen");
      exit(EXIT_FAILURE);
    }
  return (ret);
}

ssize_t		xsend(int sockfd, const void *buf, size_t len, int flags)
{
  ssize_t	ret;

  if ((ret = send(sockfd, buf, len, flags)) == -1)
    {
      perror("send");
      exit(EXIT_FAILURE);
    }
  return (ret);
}
