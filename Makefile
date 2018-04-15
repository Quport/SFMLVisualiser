PROG = main
CXX = clang++
OBJ = obj/$(PROG).o obj/better_text.o obj/descriptive_circle.o \
      obj/descriptive_rectangle.o obj/device_handler.o obj/hud_render_window.o \
      obj/legend.o obj/line_shape.o obj/texture_handler.o obj/useful.o \
      obj/view_moving.o
CXXFLAGS = -std=c++11 -Wall -Wextra -Wshadow -Wfloat-equal -Wno-unused-result \
           -Wno-macro-redefined -O3
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

.PHONY: clean all

all: $(PROG)

$(PROG): $(OBJ)
	$(CXX) $(CXXFLAGS) $(SFMLFLAGS) $(OBJ) -o $(PROG)

obj/$(PROG).o: $(PROG).cpp include/all.h include/view_moving.h include/useful.h \
               include/hud_render_window.h include/device_handler.h \
               include/better_text.h include/legend.h include/descriptive_shape.h \
               include/descriptive_circle.h include/descriptive_rectangle.h \
               include/texture_handler.h include/line_shape.h | obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/%.o: src/%.cpp | obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj:
	mkdir obj

obj/better_text.o: src/better_text.cpp include/better_text.h
obj/descriptive_circle.o: src/descriptive_circle.cpp \
  include/descriptive_circle.h include/descriptive_shape.h \
  include/legend.h include/better_text.h \
  include/useful.h
obj/descriptive_rectangle.o: src/descriptive_rectangle.cpp \
  include/descriptive_rectangle.h \
  include/descriptive_shape.h include/legend.h \
  include/better_text.h include/useful.h
obj/device_handler.o: src/device_handler.cpp include/device_handler.h
obj/hud_render_window.o: src/hud_render_window.cpp \
  include/hud_render_window.h
obj/legend.o: src/legend.cpp include/legend.h \
  include/better_text.h include/useful.h
obj/line_shape.o: src/line_shape.cpp include/line_shape.h
obj/texture_handler.o: src/texture_handler.cpp \
  include/texture_handler.h
obj/useful.o: src/useful.cpp include/useful.h
obj/view_moving.o: src/view_moving.cpp include/view_moving.h

clean:
	rm -f $(OBJ) $(PROG)