NAME		  =		  incendie

FLAG          =       -W -Wall -Werror

INCLUDE       =       -I${HOME}/.froot/include/
SRC           =       incendie.c \
			incendie_main_function.c
OBJ           =       $(SRC:.c=.o)
LIBPATH       =       -L${HOME}/.froot/lib/
LIB           =       -llapin -lsfml-graphics -lsfml-audio -lsfml-window      \
  -lsfml-system -lstdc++ -lm -ldl -lpthread -lgcc_s -lavcall -g3

all:          bin
bin:          $(OBJ)
		@gcc $(OBJ) -o $(NAME) $(LIBPATH) $(LIB)

clean:
	@rm -f $(NAME)
	rm -f $(OBJ)
fclean:       clean
	@rm -f $(NAME)
re:           fclean all

.PHONY: all clean fclean re

