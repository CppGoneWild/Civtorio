CXX = clang++


SRC_IMGUI = imgui/imgui.cpp      \
            imgui/imgui_demo.cpp \
            imgui/imgui_draw.cpp \
            imgui/imgui_tables.cpp \
            imgui/imgui_widgets.cpp \
            imgui-sfml/imgui-SFML.cpp

SRC_IMPLOT = implot/implot.cpp      \
             implot/implot_items.cpp \
             implot/implot_demo.cpp


NAME_TEST_IMGUI = test_imgui.out
SRC_TEST_IMGUI  = $(SRC_IMGUI) \
                  $(SRC_IMPLOT) \
                  test_imgui.cpp
OBJ_TEST_IMGUI  = $(SRC_TEST_IMGUI:.cpp=.o)



INCLUDE_SFML_FLAGS =
INCLUDE_IMGUI_FLAGS = -Iimgui -Iimgui-sfml -Iimplot
WARNING_FLAGS = -Wall -Wextra
CXXFLAGS = -std=c++1z $(WARNING_FLAGS) $(INCLUDE_OTHER_FLAGS) $(INCLUDE_IMGUI_FLAGS) $(INCLUDE_SFML_FLAGS) -g



LD_SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system
LD_IMGUI_FLAGS = -lGL
LDFLAGS = $(LD_IMGUI_FLAGS) $(LD_SFML_FLAGS) -pthread



all : $(NAME_TEST_IMGUI)

$(NAME_TEST_IMGUI) : $(OBJ_TEST_IMGUI)
	$(CXX) -o $(NAME_TEST_IMGUI) $(OBJ_TEST_IMGUI) $(LDFLAGS)



clean :
	rm -f $(OBJ_TEST_IMGUI)

fclean : clean
	rm -f imgui.ini $(NAME_TEST_IMGUI)

re : clean all
