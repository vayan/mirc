##
## Makefile for  in /home/vailla_y/Projet/myirc/svn_my_irc/server
## 
## Made by yann vaillant
## Login   <vailla_y@epitech.net>
## 
## Started on  Thu Apr 19 11:59:27 2012 yann vaillant
## Last update Thu Apr 19 11:59:28 2012 yann vaillant
##

CC=gcc
NAME=server
SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)
CFLAGS= -W -Wall -Wextra -g -Iinclude 

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	rm -f *~
	rm -f *# 
	rm -f $(OBJ) 
	rm -f src/*~
	rm -f src/*# 
	rm -f src/$(OBJ) 

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)