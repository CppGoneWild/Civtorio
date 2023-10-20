CXX = clang++

# ROOT_SRC = ../
# EXTERNAL = $(ROOT_SRC)/../external

# SRC_IMGUI = $(EXTERNAL)/imgui/imgui.cpp      \
#             $(EXTERNAL)/imgui/imgui_demo.cpp \
#             $(EXTERNAL)/imgui/imgui_draw.cpp \
#             $(EXTERNAL)/imgui/imgui_tables.cpp \
#             $(EXTERNAL)/imgui/imgui_widgets.cpp \
#             $(EXTERNAL)/imgui-sfml/imgui-SFML.cpp

# SRC_IMPLOT = $(EXTERNAL)/implot/implot.cpp      \
#              $(EXTERNAL)/implot/implot_items.cpp \
#              $(EXTERNAL)/implot/implot_demo.cpp


# SRC_EXTENSION = $(ROOT_SRC)/math_ext.cpp \
#                 $(ROOT_SRC)/sfml_vector_ext.cpp


NAME_TEST_MAGIC_VALUE = test_magic_value.out
SRC_TEST_MAGIC_VALUE  = test_magic_value.cpp
OBJ_TEST_MAGIC_VALUE  = $(SRC_TEST_MAGIC_VALUE:.cpp=.o)



INCLUDE_SFML_FLAGS =
#INCLUDE_IMGUI_FLAGS = -I$(EXTERNAL)/imgui -I$(EXTERNAL)/imgui-sfml -I$(EXTERNAL)/implot
#INCLUDE_OTHER_FLAGS = -I$(ROOT_SRC) -I$(EXTERNAL)
WARNING_FLAGS = -Wall -Wextra
CXXFLAGS = -std=c++1z $(WARNING_FLAGS) $(INCLUDE_OTHER_FLAGS) $(INCLUDE_IMGUI_FLAGS) $(INCLUDE_SFML_FLAGS) -g



# LD_SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system
# LD_IMGUI_FLAGS = -lGL
# LDFLAGS = $(LD_IMGUI_FLAGS) $(LD_SFML_FLAGS) -pthread



all : $(NAME_TEST_MAGIC_VALUE)

$(NAME_TEST_MAGIC_VALUE) : $(OBJ_TEST_MAGIC_VALUE)
	$(CXX) -o $(NAME_TEST_MAGIC_VALUE) $(OBJ_TEST_MAGIC_VALUE) $(LDFLAGS)

clean :
	rm -f $(OBJ_TEST_MAGIC_VALUE)

fclean : clean
	rm -f imgui.ini $(NAME_TEST_MAGIC_VALUE)

re : clean all
