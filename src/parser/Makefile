CXX = clang++

NAME_TEST = test.out
SRC_TEST  = types.cpp \
            token.cpp \
            \
            test.cpp
OBJ_TEST  = $(SRC_TEST:.cpp=.o)



INCLUDE_SFML_FLAGS =
#INCLUDE_IMGUI_FLAGS = -I$(EXTERNAL)/imgui -I$(EXTERNAL)/imgui-sfml -I$(EXTERNAL)/implot
#INCLUDE_OTHER_FLAGS = -I$(ROOT_SRC) -I$(EXTERNAL)
WARNING_FLAGS = -Wall -Wextra
CXXFLAGS = -std=c++1z $(WARNING_FLAGS) $(INCLUDE_OTHER_FLAGS) $(INCLUDE_IMGUI_FLAGS) $(INCLUDE_SFML_FLAGS) -g



# LD_SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system
# LD_IMGUI_FLAGS = -lGL
# LDFLAGS = $(LD_IMGUI_FLAGS) $(LD_SFML_FLAGS) -pthread



all : $(NAME_TEST)

$(NAME_TEST) : $(OBJ_TEST)
	$(CXX) -o $(NAME_TEST) $(OBJ_TEST) $(LDFLAGS)

clean :
	rm -f $(OBJ_TEST)

fclean : clean
	rm -f $(NAME_TEST)

re : clean all
