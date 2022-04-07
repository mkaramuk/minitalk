SRCS		= src/utils.o src/ft_strncmp.o src/ft_atoi.o src/ft_printf.o src/ft_strlen.o

SRCS_MCL	= src/client.o
SRCS_BCL	= src/client_bonus.o

SRCS_MSRV	= src/server.o
SRCS_BSRV	= src/server_bonus.o

NAME_CL		= client
NAME_SRV	= server
NAME		= IGNOREIT
CFLAGS		= -I./include -Wall -Wextra -Werror

all: $(NAME_CL) $(NAME_SRV)

$(NAME): all

$(NAME_CL): $(SRCS) $(SRCS_MCL)
	gcc $(CFLAGS) $(SRCS) $(SRCS_MCL) -o $(NAME_CL)

$(NAME_SRV): $(SRCS) $(SRCS_MSRV)
	gcc $(CFLAGS) $(SRCS) $(SRCS_MSRV) -o $(NAME_SRV)


$(NAME_CL)_bonus: $(SRCS) $(SRCS_BCL)
	gcc $(CFLAGS) $(SRCS) $(SRCS_BCL) -o $(NAME_CL)_bonus

$(NAME_SRV)_bonus: $(SRCS) $(SRCS_BSRV)
	gcc $(CFLAGS) $(SRCS) $(SRCS_BSRV) -o $(NAME_SRV)_bonus

bonus: $(NAME_CL)_bonus $(NAME_SRV)_bonus 

.c.o:
	gcc $(CFLAGS) -c $< -o $@

re: fclean all

clean:
	rm -rf $(SRCS) $(SRCS_BSRV) $(SRCS_MSRV) $(SRCS_MCL) $(SRCS_BCL)

fclean: clean
	rm -rf $(NAME_CL) $(NAME_SRV) $(NAME_CL)_bonus $(NAME_SRV)_bonus

.PHONY: clean fclean all re bonus