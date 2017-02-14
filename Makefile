## -*- Makefile -*-
##
## User: andris
## Time: 13-Feb-2017 01:13:40
## Makefile created by Oracle Developer Studio.
##
## This file is generated automatically.
##


#### Compiler and tool definitions shared by all build targets #####
CCC = g++
CXX = g++
BASICOPTS = -g
CCFLAGS = $(BASICOPTS)
CXXFLAGS = $(BASICOPTS)
CCADMIN = 


# Define the target directories.
TARGETDIR_main.cpp=GNU-amd64-Linux


all: $(TARGETDIR_main.cpp)/main.cpp

## Target: main.cpp
OBJS_main.cpp =  \
	$(TARGETDIR_main.cpp)/main.o \
	$(TARGETDIR_main.cpp)/dirbuilder.o \
	$(TARGETDIR_main.cpp)/FTree.o
USERLIBS_main.cpp = -lboost_program_options -lboost_system -lboost_filesystem $(SYSLIBS_main.cpp) 
DEPLIBS_main.cpp =     
LDLIBS_main.cpp = $(USERLIBS_main.cpp)


# Link or archive
$(TARGETDIR_main.cpp)/main.cpp: $(TARGETDIR_main.cpp) $(OBJS_main.cpp) $(DEPLIBS_main.cpp)
	$(LINK.cc) $(CCFLAGS_main.cpp) $(CPPFLAGS_main.cpp) -o $@ $(OBJS_main.cpp) $(LDLIBS_main.cpp)


# Compile source files into .o files
$(TARGETDIR_main.cpp)/main.o: $(TARGETDIR_main.cpp) main.cpp
	$(COMPILE.cc) $(CCFLAGS_main.cpp) $(CPPFLAGS_main.cpp) -o $@ main.cpp

$(TARGETDIR_main.cpp)/dirbuilder.o: $(TARGETDIR_main.cpp) dirbuilder/dirbuilder.cpp
	$(COMPILE.cc) $(CCFLAGS_main.cpp) $(CPPFLAGS_main.cpp) -o $@ dirbuilder/dirbuilder.cpp

$(TARGETDIR_main.cpp)/FTree.o: $(TARGETDIR_main.cpp) FTree/FTree.cpp
	$(COMPILE.cc) $(CCFLAGS_main.cpp) $(CPPFLAGS_main.cpp) -o $@ FTree/FTree.cpp



#### Clean target deletes all generated files ####
clean:
	rm -f \
		$(TARGETDIR_main.cpp)/main.cpp \
		$(TARGETDIR_main.cpp)/main.o \
		$(TARGETDIR_main.cpp)/dirbuilder.o \
		$(TARGETDIR_main.cpp)/FTree.o
	$(CCADMIN)
	rm -f -r $(TARGETDIR_main.cpp)


# Create the target directory (if needed)
$(TARGETDIR_main.cpp):
	mkdir -p $(TARGETDIR_main.cpp)


# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.GNU-amd64-Linux

