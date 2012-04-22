/*
** xfunc.c for  in /home/vailla_y/Projet/myirc/svn_my_irc/server/src
**
** Made by yann vaillant
** Login   <vailla_y@epitech.net>
**
** Started on  Sun Apr 22 21:59:05 2012 yann vaillant
** Last update Sun Apr 22 22:24:18 2012 yann vaillant
*/

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "server.h"

int	xclose(int d)
{
  if (close(d) == -1)
    {
      perror("close");
      return (-1);
    }
  return (0);
}

void		*xmalloc(unsigned int size)
{
  void		*p;

  if ((p = malloc(size)) == 0)
    {
      printf("Fail Malloc\n");
      exit(EXIT_FAILURE);
    }
  return (p);
}

sighandler_t	xsignal(int signum, sighandler_t handler)
{
  sighandler_t	ret;

  ret = signal(signum, handler);
  if (ret == SIG_ERR)
    {
      perror("signal");
      exit(EXIT_FAILURE);
    }
  return (ret);
}

int	xbind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
  int	ret;

  if ((ret = bind(sockfd, addr, addrlen)) == -1)
  {
    perror("bind");
    exit(EXIT_FAILURE);
  }
  return (ret);
}

