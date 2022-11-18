CC = gcc

NAME = ft_ls

FT_LS_LIBRARY = ft_ls.a

LIBFT = libft/

FT_PRINTF = ft_printf

FLAGS = -Wall -Wextra -Werror

FT_LS_SRCS =  $(shell find ./srcs -type f -name '*.c')

FT_LS_OBJS = $(FT_LS_SRCS:.c=.o)

PWD = $(shell pwd)

.c.o:
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(FT_LS_OBJS)
	@ar rc $(FT_LS_LIBRARY) $(FT_LS_OBJS)
	@ranlib $(FT_LS_LIBRARY)
	make -C $(FT_PRINTF) all
	make -C $(LIBFT) all
	$(CC) main.c $(FT_LS_LIBRARY) libft/libft.a ft_printf/libftprintf.a -o $(NAME)

docker:
	@docker build -t ft_ls_image .
	@docker run  --name ft_ls_container -it --rm -v $(PWD):/ft_ls ft_ls_image /bin/bash

clean:
	rm -rf $(FT_LS_OBJS) $(FT_LS_LIBRARY)
	
fclean:	clean
	rm -rf $(NAME) 
	make -C $(LIBFT) fclean
	-docker image rm ft_ls_image

re: fclean all