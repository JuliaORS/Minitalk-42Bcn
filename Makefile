# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julolle- <julolle-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/15 15:23:31 by julolle-          #+#    #+#              #
#    Updated: 2023/08/28 12:58:31 by julolle-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAMES		:= server

NAMEC		:= client

SERVERSRCS	:= server.c

CLIENTSRCS	:= client.c

PRINTF_DIR  := ft_printf/
PRINTF		:= $(PRINTF_DIR)/libftprintf.a

SERVEROBJS	:= $(SERVERSRCS:.c=.o)
CLIENTOBJS	:= $(CLIENTSRCS:.c=.o)	

CLIENTDEPS	:= $(CLIENTSRCS:.c=.d)
SERVERDEPS	:= $(SERVERSRCS:.c=.d)

CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror -MMD

INCLUDE		:= -I ft_printf/

RM			:= @rm -fv

#Implicit Method
%.o: %.c	Makefile $(PRINTF)
	@$(CC) $(CFLAGS) ${INCLUDE} -c -o $@ $< 
	
# My methods
all:	M_PRINTF $(NAMES) $(NAMEC)

M_PRINTF:
	@make  -C $(PRINTF_DIR) 

$(NAMES): $(SERVEROBJS)
	${CC} ${SERVEROBJS} -L $(PRINTF_DIR) -lftprintf -o ${NAMES}

$(NAMEC): $(CLIENTOBJS)
	${CC} ${CLIENTOBJS} -L $(PRINTF_DIR) -lftprintf -o ${NAMEC}

clean:
	@make clean -C $(PRINTF_DIR) 
	$(RM) $(SERVEROBJS) $(CLIENTOBJS) $(CLIENTDEPS) $(SERVERDEPS)

fclean: 
	$(RM) $(SERVEROBJS) $(CLIENTOBJS) $(CLIENTDEPS) $(SERVERDEPS)
	@make fclean -C $(PRINTF_DIR) 
	$(RM) $(NAMES) $(NAMEC)

re:	fclean all

-include $(CLIENTDEPS) $(SERVERDEPS)

# Phony
.PHONY: all clean fclean re
