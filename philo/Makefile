# ************************************************************************** #
#                                                                            #
#                                                        :::      ::::::::   #
#   Makefile                                           :+:      :+:    :+:   #
#                                                    +:+ +:+         +:+     #
#   By: hachi-gbg <dev@hachi868.com>               +#+  +:+       +#+        #
#                                                +#+#+#+#+#+   +#+           #
#   Created: 2023/01/10 01:31:43 by hachi-gbg         #+#    #+#             #
#   Updated: 2023/04/08 20:28:59 by hachi-gbg        ###   ########.fr       #                                                              #
# ************************************************************************** #

PROG := philo

CC := cc
CFLAGS := -Wall -Wextra -Werror
LDFLAGS = -lpthread
SRCS =	main.c\
		init_simulation.c\
		init_philo.c\
		state_change/eating01.c\
		state_change/eating02.c\
		state_change/sleeping.c\
		state_change/thinking.c\
		state_change/died.c\
		utils/memory.c\
		utils/get_time.c\
		utils/ft_atoi_unsigned.c\
		utils/check_error.c\
		utils/print.c\
		utils/ft_mutex.c

OBJS := $(SRCS:.c=.o)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS)

all: $(PROG)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(PROG)

re:	fclean all

.PHONY:	all clean fclean re
