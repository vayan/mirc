/*
** server.h for  in /home/vailla_y/Projet/myirc/svn_my_irc/server
**
** Made by yann vaillant
** Login   <vailla_y@epitech.net>
**
** Started on  Sun Apr 22 21:24:18 2012 yann vaillant
** Last update Sun Apr 22 22:26:19 2012 yann vaillant
*/

#ifndef SERVER_H
#define SERVER_H

#define MAX_INPUT 50000

typedef void (*sighandler_t)(int);

typedef	struct			s_client {
	int			fd;
	char			*channel;
	char			*nick;
	struct	s_client	*next;
}				t_client;

void			aff_all_client(t_client *all_client);
void			select_list(t_client *all_client, fd_set *readf);
int			get_higher_fd(t_client *all_client);
char			*rand_str(char *dst, int size);
t_client		*add_client(t_client *all_client, int fd);
int			broadcast_to_all_client(t_client *all_client, char *msg,
						char *channel, t_client *me);
int			broadcast_to_one_client(char *msg, t_client *me);
int			broadcast_to_all_client_but_me(t_client *all_client,
						       char *msg, char *channel,
						       t_client *me);
int			join_channel(t_client *client, char *ch_name);
int			change_nick(t_client *client, char *new_nick);
int			leave_channel(t_client *client);
int			get_cmd_client(t_client *client, char *msg);
void			get_data_from_client(t_client *all_client,
					     fd_set *readfs);
t_client		*get_all_client(t_client *_all_client);
t_client		*get_client_by_nick(char *nick);
int			list_channel(t_client *client, t_client *me,
				     char *channel);
int			list_user(t_client *all_client, t_client *me);
int			send_msg(t_client *me, char *messsag, char *dest_nick);
int			xclose(int d);
void			*xmalloc(unsigned int size);
sighandler_t		xsignal(int signum, sighandler_t handler);
int			xbind(int sockfd, const struct sockaddr *addr,
			      socklen_t addrlen);
int			xlisten(int sockfd, int backlog);
ssize_t			xsend(int sockfd, const void *buf,
			      size_t len, int flags);

#endif
