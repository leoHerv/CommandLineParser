CXXFLAGS = -std=c++17 -O3

# List of the .cpp files for the library that we put in SRCLIB.
SRCLIB = lib/commands/command/command.cpp \
       lib/commands/helpCommand/helpCommand.cpp \
       lib/target/target.cpp \
       lib/parser/parser.cpp

# List of the .cpp files for the program that we put in SRCPROG.
SRCPROG = src/main.cpp \
	   src/commands/additionCommand/additionCommand.h \
	   src/commands/helloCommand/helloCommand.h \
	   src/commands/instantTriggerCommand/instantTriggerCommand.h \
	   src/commands/laterCommand/laterCommand.h \
	   src/commands/requiredCommand/requiredCommand.h

# We transform the .cpp files in .o to put their paths in OBJS.
OBJS = $(SRCLIB:.cpp=.o)

all: program

# Demo program creation.
program: lib
	@ g++ $(CXXFLAGS) -o program $(SRCPROG) \
	-L $(CURDIR) -lparser
	@echo "Program creation done."

# Lib creation.
lib: $(OBJS)
	@ ar rcs libparser.a $(OBJS)
	@echo "Lib creation done."

# .o files creation.
%.o: %.cpp
	@ g++ $(CXXFLAGS) -c $< -o $@

# Remove all the .o files generated, the executable and the lib.
clean:
	@ rm -f program libparser.a $(OBJS)
	@echo "Clean done."