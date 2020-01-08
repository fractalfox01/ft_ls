NAME= ft_ls

SRC := $(addsuffix .c, src/main src/verify_options src/set_options src/init_utils \
	src/option_utils src/verify_args src/set_arguments src/ls_utils)

INC := $(addsuffix .h, includes/ft_ls includes/ft_printf includes/get_next_line \
	includes/libft)

FLAGS= -Wall -Werror -Wextra

$(NAME):
	gcc -g $(FLAGS) libft.a $(SRC) -o ft_ls

all: $(NAME)

clean:
	rm ft_ls 2>/dev/null | echo "Gone"
	rm -rf ft_ls.dSYM/ 2>/dev/null | echo "Gone"

fclean: clean

fc: fclean

re: fclean all

add:
	git add makefile $(SRC) $(INC)
	git status

push:
	git commit -m "auto push"
	git push
