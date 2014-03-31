NAME=		test_compilo

SRC=		Controller.cpp 	\
				Convers.cpp			\
				Core.cpp				\
				Friends.cpp			\
				Group.cpp				\
				Popup.cpp				\
				Profile.cpp			\
				Race.cpp				\
				Setting.cpp			\
				SignInUp.cpp		\
				Tooltip.cpp			\
				main_test.cpp

OBJ=		$(SRC:.cpp=.o)

CXXFLAGS=	-I../../includes/ -std=c++11 -Wall -Wextra -g -ggdb

CXX=		clang++

all:	$(NAME)	

$(NAME):	$(OBJ)
	$(CXX) -o $(NAME) $(OBJ) -I../../includes

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all
