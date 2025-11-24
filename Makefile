NAME := FJA

CXX := c++
CXXFLAGS := -Wall -Werror -Wextra -std=c++23 -MMD -MP
DEBUGFLAGS := -DDEBUG  # Add debug macro

SRC := main.cpp \
	FJA.cpp \
	utils.cpp

OBJDIR := obj
OBJ := $(OBJDIR)/main.o \
		$(OBJDIR)/FJA.o \
		$(OBJDIR)/utils.o

OBJDEBUG := $(OBJDIR)/main_debug.o \
		$(OBJDIR)/FJA_debug.o \
		$(OBJDIR)/utils_debug.o

DEP := $(OBJ:.o=.d)
DEPDEBUG := $(OBJDEBUG:.o=.d)

# Regular build (no debug prints)
all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)

# Debug build (with prints)
test: $(OBJDEBUG)
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) -o $(NAME)_debug $(OBJDEBUG)

$(OBJDIR)/main.o: main.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c main.cpp -o $(OBJDIR)/main.o

$(OBJDIR)/FJA.o: FJA.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c FJA.cpp -o $(OBJDIR)/FJA.o

$(OBJDIR)/main_debug.o: main.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) -c main.cpp -o $(OBJDIR)/main_debug.o

$(OBJDIR)/FJA_debug.o: FJA.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) -c FJA.cpp -o $(OBJDIR)/FJA_debug.o

$(OBJDIR)/utils.o: utils.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c utils.cpp -o $(OBJDIR)/utils.o

$(OBJDIR)/utils_debug.o: utils.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(DEBUGFLAGS) -c utils.cpp -o $(OBJDIR)/utils_debug.o

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME) $(NAME)_debug

re: fclean all

run: $(NAME)
	./$(NAME)

run_debug: test
	./$(NAME)_debug

.PHONY: all clean fclean re run test run_debug

# Include automatically generated header dependencies (ignore if not yet present)
-include $(DEP)
-include $(DEPDEBUG)
