CXX = clang++

ROOT_SRC = ../
EXTERNAL = $(ROOT_SRC)/../external

SRC_IMGUI = $(EXTERNAL)/imgui/imgui.cpp      \
            $(EXTERNAL)/imgui/imgui_demo.cpp \
            $(EXTERNAL)/imgui/imgui_draw.cpp \
            $(EXTERNAL)/imgui/imgui_tables.cpp \
            $(EXTERNAL)/imgui/imgui_widgets.cpp \
            $(EXTERNAL)/imgui-sfml/imgui-SFML.cpp

SRC_IMPLOT = $(EXTERNAL)/implot/implot.cpp      \
             $(EXTERNAL)/implot/implot_items.cpp \
             $(EXTERNAL)/implot/implot_demo.cpp


# SRC_EXTENSION = $(ROOT_SRC)/math_ext.cpp \
#                 $(ROOT_SRC)/sfml_vector_ext.cpp


NAME_TEST_HUMAN_READABLE_FORMATER = test_human_readable_formater.out
SRC_TEST_HUMAN_READABLE_FORMATER  = HumanReadableFormater.cpp \
                                    \
                                    test_HumanReadableFormater.cpp
OBJ_TEST_HUMAN_READABLE_FORMATER  = $(SRC_TEST_HUMAN_READABLE_FORMATER:.cpp=.o)


NAME_DEMO_HUMAN_READABLE_FORMATER = demo_human_readable_formater.out
SRC_DEMO_HUMAN_READABLE_FORMATER  = $(SRC_IMGUI) \
                                    $(SRC_IMPLOT) \
                                    \
                                    HumanReadableFormater.cpp \
                                    HumanReadableFormater_imgui.cpp \
                                    \
                                    demo_HumanReadableFormater.cpp
OBJ_DEMO_HUMAN_READABLE_FORMATER  = $(SRC_DEMO_HUMAN_READABLE_FORMATER:.cpp=.o)



INCLUDE_SFML_FLAGS =
INCLUDE_IMGUI_FLAGS = -I$(EXTERNAL)/imgui -I$(EXTERNAL)/imgui-sfml -I$(EXTERNAL)/implot
INCLUDE_OTHER_FLAGS = -I$(ROOT_SRC) -I$(EXTERNAL)
WARNING_FLAGS = -Wall -Wextra
CXXFLAGS = -std=c++1z $(WARNING_FLAGS) $(INCLUDE_OTHER_FLAGS) $(INCLUDE_IMGUI_FLAGS) $(INCLUDE_SFML_FLAGS) -g



LD_SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system
LD_IMGUI_FLAGS = -lGL
LDFLAGS = $(LD_IMGUI_FLAGS) $(LD_SFML_FLAGS) -pthread



all : $(NAME_TEST_HUMAN_READABLE_FORMATER) $(NAME_DEMO_HUMAN_READABLE_FORMATER)

$(NAME_TEST_HUMAN_READABLE_FORMATER) : $(OBJ_TEST_HUMAN_READABLE_FORMATER)
	$(CXX) -o $(NAME_TEST_HUMAN_READABLE_FORMATER) $(OBJ_TEST_HUMAN_READABLE_FORMATER) $(LDFLAGS)

$(NAME_DEMO_HUMAN_READABLE_FORMATER) : $(OBJ_DEMO_HUMAN_READABLE_FORMATER)
	$(CXX) -o $(NAME_DEMO_HUMAN_READABLE_FORMATER) $(OBJ_DEMO_HUMAN_READABLE_FORMATER) $(LDFLAGS)

clean :
	rm -f $(OBJ_TEST_HUMAN_READABLE_FORMATER) $(OBJ_DEMO_HUMAN_READABLE_FORMATER)

fclean : clean
	rm -f imgui.ini $(NAME_TEST_HUMAN_READABLE_FORMATER) $(NAME_DEMO_HUMAN_READABLE_FORMATER)

re : clean all
