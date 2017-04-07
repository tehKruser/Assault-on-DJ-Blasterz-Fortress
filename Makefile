#########################################################
# File: Makefile
# Description: A more robust makefile for CS162.
# You need to edit the variables under "USER SECTION".
# To execute the makefile on unix-y systems, type 'make'.
# If that doesn't work, 'make -f makefile' might be useful.
#########################################################

# #'s are line-comments 

# CXX is a standard variable name used for the compiler. 
CXX = g++

# CXXFLAGS is a standard variable name for compile flags.
# -std=c++0x specifies to use a certain language version.
CXXFLAGS = -std=c++0x

# -Wall turns on all warnings
CXXFLAGS += -Wall

# -pedantic-errors strictly enforces the standard
CXXFLAGS += -pedantic-errors

# -g turns on debug information 
CXXFLAGS += -g

####################
### USER SECTION ###
####################

# SRCS is a standard name for the source files. 
# Edit as needed.
SRC1 = main.cpp
SRC2 = MyFunctions.cpp
SRC3 = ConsoleManip.cpp
SRC4 = ColorRoom.cpp
SRC5 = ControlRoom.cpp
SRC6 = FinalBossRoom.cpp
SRC7 = Hero.cpp
SRC8 = Item.cpp
SRC9 = Queue.cpp
SRC10 = StartRoom.cpp
SRC11 = Weapon.cpp
SRC12 = Space.cpp
SRCS = ${SRC1} ${SRC2} ${SRC3} ${SRC4} ${SRC5} ${SRC6} ${SRC7} ${SRC8} ${SRC9} ${SRC10} ${SRC11} ${SRC12}

# HEADERS is a standard name for the header files. 
# Edit these as needed.
HEADER1 = MyFunctions.hpp
HEADER2 = ConsoleManip.hpp
HEADER3 = ColorRoom.hpp
HEADER4 = ControlRoom.hpp
HEADER5 = FinalBossRoom.hpp
HEADER6 = Hero.hpp
HEADER7 = Item.hpp
HEADER8 = Queue.hpp
HEADER9 = StartRoom.hpp
HEADER10 = Weapon.hpp
HEADER11 = Space.hpp
HEADERS = ${HEADER1} ${HEADER2} ${HEADER3} ${HEADER4} ${HEADER5} ${HEADER6} ${HEADER7} ${HEADER8} ${HEADER9} ${HEADER10} ${HEADER11}

HEADERS = ${HEADER1} ${HEADER2}

# These will be your executable names. 
# Edit as needed.
PROG1 = final
PROGS = ${PROG1}

# This is the name of your document(s). 
# Edit as needed.
DOC = kruse_justin_modA_writeup.pdf

# This is the name of your compressed file. 
# Edit name as needed. Keep the format.
TAR = cs162_moduleA_krusej.tar.bz2

#####################
### BUILD SECTION ###
#####################

# Typing 'make' in terminal calls the first build availible.
# In this case, default.
default:
	${CXX} ${CXXFLAGS} ${SRCS} ${HEADERS} -o ${PROG1}

# Typing 'make all' in terminal calls this build.
all:
	${CXX} ${CXXFLAGS} ${SRCS} ${HEADERS} -o ${PROG1}

# Typing 'make tar' in terminal calls this build.
# This creates a compressed file for submission.
tar:
	tar cvjf ${TAR} ${SRCS} ${HEADERS} ${DOC} makefile

# Typing 'make clean' calls this build.
# It's designed to clean up the folder.
# Be careful with this, edit as needed.
clean: 
	rm -f ${PROGS} *.o *~

