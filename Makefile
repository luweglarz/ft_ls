CC = gcc

NAME = ft_ls

LIB = ft_ls.a

LIBFT = libft/

FLAGS = -Wall -Wextra -Werror

SRCS =  $(shell find ./srcs -type f -name '*.c')

OBJS = $(SRCS:.c=.o)

PWD = $(shell pwd)

.c.o:
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@ar rc $(LIB) $(OBJS)
	@ranlib $(LIB)
	make -C $(LIBFT) all
	$(CC) $(FLAGS) main.c $(LIB) $(LIBFT)libft.a -o $(NAME)

docker:
	@docker build -t image .
	@docker run  --name container -it --rm -v $(PWD):/ft_ls image /bin/bash

clean:
	rm -rf $(OBJS) $(LIB)
	
fclean:	clean
	rm -rf $(NAME) 
	make -C $(LIBFT) fclean
	-docker image rm image

re: fclean all