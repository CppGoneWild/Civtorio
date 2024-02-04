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


SFML_EXT = $(ROOT_SRC)/math_ext.cpp \
           $(ROOT_SRC)/sfml_ext/sfml_vector_array.cpp \
           $(ROOT_SRC)/sfml_ext/sfml_vector_ext.cpp

SRC_WIN_MNGR = $(ROOT_SRC)/win_mngr/show_info.cpp


NAME_DEMO_TECHNO = demo_techno.out
SRC_DEMO_TECHNO  = $(SRC_IMGUI) \
                   $(SRC_IMPLOT) \
                   $(SFML_EXT) \
                   $(SRC_WIN_MNGR) \
                   \
                   techno_base.cpp \
                   \
                   demo_techno.cpp
OBJ_DEMO_TECHNO  = $(SRC_DEMO_TECHNO:.cpp=.o)



INCLUDE_SFML_FLAGS =
INCLUDE_IMGUI_FLAGS = -I$(EXTERNAL)/imgui -I$(EXTERNAL)/imgui-sfml -I$(EXTERNAL)/implot
INCLUDE_OTHER_FLAGS = -I$(ROOT_SRC) -I$(EXTERNAL)
WARNING_FLAGS = -Wall -Wextra
CXXFLAGS = -std=c++1z $(WARNING_FLAGS) $(INCLUDE_OTHER_FLAGS) $(INCLUDE_IMGUI_FLAGS) $(INCLUDE_SFML_FLAGS) -g



LD_SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system
LD_IMGUI_FLAGS = -lGL
LDFLAGS = $(LD_IMGUI_FLAGS) $(LD_SFML_FLAGS) -pthread



all : $(NAME_DEMO_TECHNO)

$(NAME_DEMO_TECHNO) : $(OBJ_DEMO_TECHNO)
	$(CXX) -o $(NAME_DEMO_TECHNO) $(OBJ_DEMO_TECHNO) $(LDFLAGS)



clean :
	rm -f $(OBJ_DEMO_TECHNO)

fclean : clean
	rm -f imgui.ini $(NAME_DEMO_TECHNO)

re : clean all
