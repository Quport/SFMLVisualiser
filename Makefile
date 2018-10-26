PROG = main
CXX = clang++
OBJ = $(PROG).o src/better_text.o src/descriptive_circle.o \
      src/descriptive_rectangle.o src/device_handler.o src/hud_render_window.o \
      src/legend.o src/line_shape.o src/texture_handler.o src/useful.o \
      src/view_moving.o
CXX_FLAGS = -std=c++17 -Wall -Wextra -Wshadow -Wfloat-equal \
            -Wno-unused-result -O3
DEBUG_FLAGS = -fsanitize=address -g
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

.PHONY: clean all

all: $(PROG)

debug: CXX_FLAGS += $(DEBUG_FLAGS)
debug: all

$(PROG): $(OBJ)
	$(CXX) $(CXX_FLAGS) $(SFML_FLAGS) $(OBJ) -o $(PROG)

%.o: %.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

src/better_text.o: src/better_text.cpp include/better_text.h
src/descriptive_circle.o: src/descriptive_circle.cpp \
  include/descriptive_circle.h include/descriptive_shape.h \
  include/legend.h include/better_text.h \
  include/useful.h
src/descriptive_rectangle.o: src/descriptive_rectangle.cpp \
  include/descriptive_rectangle.h \
  include/descriptive_shape.h include/legend.h \
  include/better_text.h include/useful.h
src/device_handler.o: src/device_handler.cpp include/device_handler.h
src/hud_render_window.o: src/hud_render_window.cpp \
  include/hud_render_window.h
src/legend.o: src/legend.cpp include/legend.h \
  include/better_text.h include/useful.h
src/line_shape.o: src/line_shape.cpp include/line_shape.h
src/texture_handler.o: src/texture_handler.cpp \
  include/texture_handler.h
src/useful.o: src/useful.cpp include/useful.h
src/view_moving.o: src/view_moving.cpp include/view_moving.h
$(PROG).o: $(PROG).cpp include/all.h include/view_moving.h include/useful.h \
           include/hud_render_window.h include/device_handler.h \
           include/better_text.h include/legend.h include/descriptive_shape.h \
           include/descriptive_circle.h include/descriptive_rectangle.h \
           include/texture_handler.h include/line_shape.h

clean:
	rm -f $(OBJ) $(PROG)
