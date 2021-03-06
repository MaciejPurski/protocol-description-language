# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/clion-2018.1.1/bin/cmake/bin/cmake

# The command to remove a file.
RM = /opt/clion-2018.1.1/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/maciej/tkom/protocol-description-language

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/maciej/tkom/protocol-description-language

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/opt/clion-2018.1.1/bin/cmake/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/opt/clion-2018.1.1/bin/cmake/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/maciej/tkom/protocol-description-language/CMakeFiles /home/maciej/tkom/protocol-description-language/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/maciej/tkom/protocol-description-language/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named TKOM

# Build rule for target.
TKOM: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 TKOM
.PHONY : TKOM

# fast build rule for target.
TKOM/fast:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/build
.PHONY : TKOM/fast

Analyzer/AnalyzerField.o: Analyzer/AnalyzerField.cpp.o

.PHONY : Analyzer/AnalyzerField.o

# target to build an object file
Analyzer/AnalyzerField.cpp.o:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Analyzer/AnalyzerField.cpp.o
.PHONY : Analyzer/AnalyzerField.cpp.o

Analyzer/AnalyzerField.i: Analyzer/AnalyzerField.cpp.i

.PHONY : Analyzer/AnalyzerField.i

# target to preprocess a source file
Analyzer/AnalyzerField.cpp.i:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Analyzer/AnalyzerField.cpp.i
.PHONY : Analyzer/AnalyzerField.cpp.i

Analyzer/AnalyzerField.s: Analyzer/AnalyzerField.cpp.s

.PHONY : Analyzer/AnalyzerField.s

# target to generate assembly for a file
Analyzer/AnalyzerField.cpp.s:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Analyzer/AnalyzerField.cpp.s
.PHONY : Analyzer/AnalyzerField.cpp.s

Analyzer/AnalyzerPacket.o: Analyzer/AnalyzerPacket.cpp.o

.PHONY : Analyzer/AnalyzerPacket.o

# target to build an object file
Analyzer/AnalyzerPacket.cpp.o:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Analyzer/AnalyzerPacket.cpp.o
.PHONY : Analyzer/AnalyzerPacket.cpp.o

Analyzer/AnalyzerPacket.i: Analyzer/AnalyzerPacket.cpp.i

.PHONY : Analyzer/AnalyzerPacket.i

# target to preprocess a source file
Analyzer/AnalyzerPacket.cpp.i:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Analyzer/AnalyzerPacket.cpp.i
.PHONY : Analyzer/AnalyzerPacket.cpp.i

Analyzer/AnalyzerPacket.s: Analyzer/AnalyzerPacket.cpp.s

.PHONY : Analyzer/AnalyzerPacket.s

# target to generate assembly for a file
Analyzer/AnalyzerPacket.cpp.s:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Analyzer/AnalyzerPacket.cpp.s
.PHONY : Analyzer/AnalyzerPacket.cpp.s

Analyzer/PacketsScanner.o: Analyzer/PacketsScanner.cpp.o

.PHONY : Analyzer/PacketsScanner.o

# target to build an object file
Analyzer/PacketsScanner.cpp.o:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Analyzer/PacketsScanner.cpp.o
.PHONY : Analyzer/PacketsScanner.cpp.o

Analyzer/PacketsScanner.i: Analyzer/PacketsScanner.cpp.i

.PHONY : Analyzer/PacketsScanner.i

# target to preprocess a source file
Analyzer/PacketsScanner.cpp.i:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Analyzer/PacketsScanner.cpp.i
.PHONY : Analyzer/PacketsScanner.cpp.i

Analyzer/PacketsScanner.s: Analyzer/PacketsScanner.cpp.s

.PHONY : Analyzer/PacketsScanner.s

# target to generate assembly for a file
Analyzer/PacketsScanner.cpp.s:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Analyzer/PacketsScanner.cpp.s
.PHONY : Analyzer/PacketsScanner.cpp.s

Interpreter.o: Interpreter.cpp.o

.PHONY : Interpreter.o

# target to build an object file
Interpreter.cpp.o:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Interpreter.cpp.o
.PHONY : Interpreter.cpp.o

Interpreter.i: Interpreter.cpp.i

.PHONY : Interpreter.i

# target to preprocess a source file
Interpreter.cpp.i:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Interpreter.cpp.i
.PHONY : Interpreter.cpp.i

Interpreter.s: Interpreter.cpp.s

.PHONY : Interpreter.s

# target to generate assembly for a file
Interpreter.cpp.s:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Interpreter.cpp.s
.PHONY : Interpreter.cpp.s

Nodes/AltOperation.o: Nodes/AltOperation.cpp.o

.PHONY : Nodes/AltOperation.o

# target to build an object file
Nodes/AltOperation.cpp.o:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Nodes/AltOperation.cpp.o
.PHONY : Nodes/AltOperation.cpp.o

Nodes/AltOperation.i: Nodes/AltOperation.cpp.i

.PHONY : Nodes/AltOperation.i

# target to preprocess a source file
Nodes/AltOperation.cpp.i:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Nodes/AltOperation.cpp.i
.PHONY : Nodes/AltOperation.cpp.i

Nodes/AltOperation.s: Nodes/AltOperation.cpp.s

.PHONY : Nodes/AltOperation.s

# target to generate assembly for a file
Nodes/AltOperation.cpp.s:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Nodes/AltOperation.cpp.s
.PHONY : Nodes/AltOperation.cpp.s

Nodes/Block.o: Nodes/Block.cpp.o

.PHONY : Nodes/Block.o

# target to build an object file
Nodes/Block.cpp.o:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Nodes/Block.cpp.o
.PHONY : Nodes/Block.cpp.o

Nodes/Block.i: Nodes/Block.cpp.i

.PHONY : Nodes/Block.i

# target to preprocess a source file
Nodes/Block.cpp.i:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Nodes/Block.cpp.i
.PHONY : Nodes/Block.cpp.i

Nodes/Block.s: Nodes/Block.cpp.s

.PHONY : Nodes/Block.s

# target to generate assembly for a file
Nodes/Block.cpp.s:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Nodes/Block.cpp.s
.PHONY : Nodes/Block.cpp.s

Nodes/Expression.o: Nodes/Expression.cpp.o

.PHONY : Nodes/Expression.o

# target to build an object file
Nodes/Expression.cpp.o:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Nodes/Expression.cpp.o
.PHONY : Nodes/Expression.cpp.o

Nodes/Expression.i: Nodes/Expression.cpp.i

.PHONY : Nodes/Expression.i

# target to preprocess a source file
Nodes/Expression.cpp.i:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Nodes/Expression.cpp.i
.PHONY : Nodes/Expression.cpp.i

Nodes/Expression.s: Nodes/Expression.cpp.s

.PHONY : Nodes/Expression.s

# target to generate assembly for a file
Nodes/Expression.cpp.s:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Nodes/Expression.cpp.s
.PHONY : Nodes/Expression.cpp.s

Nodes/Field.o: Nodes/Field.cpp.o

.PHONY : Nodes/Field.o

# target to build an object file
Nodes/Field.cpp.o:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Nodes/Field.cpp.o
.PHONY : Nodes/Field.cpp.o

Nodes/Field.i: Nodes/Field.cpp.i

.PHONY : Nodes/Field.i

# target to preprocess a source file
Nodes/Field.cpp.i:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Nodes/Field.cpp.i
.PHONY : Nodes/Field.cpp.i

Nodes/Field.s: Nodes/Field.cpp.s

.PHONY : Nodes/Field.s

# target to generate assembly for a file
Nodes/Field.cpp.s:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Nodes/Field.cpp.s
.PHONY : Nodes/Field.cpp.s

Nodes/Packet.o: Nodes/Packet.cpp.o

.PHONY : Nodes/Packet.o

# target to build an object file
Nodes/Packet.cpp.o:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Nodes/Packet.cpp.o
.PHONY : Nodes/Packet.cpp.o

Nodes/Packet.i: Nodes/Packet.cpp.i

.PHONY : Nodes/Packet.i

# target to preprocess a source file
Nodes/Packet.cpp.i:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Nodes/Packet.cpp.i
.PHONY : Nodes/Packet.cpp.i

Nodes/Packet.s: Nodes/Packet.cpp.s

.PHONY : Nodes/Packet.s

# target to generate assembly for a file
Nodes/Packet.cpp.s:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Nodes/Packet.cpp.s
.PHONY : Nodes/Packet.cpp.s

Nodes/PacketReference.o: Nodes/PacketReference.cpp.o

.PHONY : Nodes/PacketReference.o

# target to build an object file
Nodes/PacketReference.cpp.o:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Nodes/PacketReference.cpp.o
.PHONY : Nodes/PacketReference.cpp.o

Nodes/PacketReference.i: Nodes/PacketReference.cpp.i

.PHONY : Nodes/PacketReference.i

# target to preprocess a source file
Nodes/PacketReference.cpp.i:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Nodes/PacketReference.cpp.i
.PHONY : Nodes/PacketReference.cpp.i

Nodes/PacketReference.s: Nodes/PacketReference.cpp.s

.PHONY : Nodes/PacketReference.s

# target to generate assembly for a file
Nodes/PacketReference.cpp.s:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Nodes/PacketReference.cpp.s
.PHONY : Nodes/PacketReference.cpp.s

Nodes/Protocol.o: Nodes/Protocol.cpp.o

.PHONY : Nodes/Protocol.o

# target to build an object file
Nodes/Protocol.cpp.o:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Nodes/Protocol.cpp.o
.PHONY : Nodes/Protocol.cpp.o

Nodes/Protocol.i: Nodes/Protocol.cpp.i

.PHONY : Nodes/Protocol.i

# target to preprocess a source file
Nodes/Protocol.cpp.i:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Nodes/Protocol.cpp.i
.PHONY : Nodes/Protocol.cpp.i

Nodes/Protocol.s: Nodes/Protocol.cpp.s

.PHONY : Nodes/Protocol.s

# target to generate assembly for a file
Nodes/Protocol.cpp.s:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Nodes/Protocol.cpp.s
.PHONY : Nodes/Protocol.cpp.s

Nodes/RepeatOperation.o: Nodes/RepeatOperation.cpp.o

.PHONY : Nodes/RepeatOperation.o

# target to build an object file
Nodes/RepeatOperation.cpp.o:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Nodes/RepeatOperation.cpp.o
.PHONY : Nodes/RepeatOperation.cpp.o

Nodes/RepeatOperation.i: Nodes/RepeatOperation.cpp.i

.PHONY : Nodes/RepeatOperation.i

# target to preprocess a source file
Nodes/RepeatOperation.cpp.i:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Nodes/RepeatOperation.cpp.i
.PHONY : Nodes/RepeatOperation.cpp.i

Nodes/RepeatOperation.s: Nodes/RepeatOperation.cpp.s

.PHONY : Nodes/RepeatOperation.s

# target to generate assembly for a file
Nodes/RepeatOperation.cpp.s:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Nodes/RepeatOperation.cpp.s
.PHONY : Nodes/RepeatOperation.cpp.s

Nodes/Sequence.o: Nodes/Sequence.cpp.o

.PHONY : Nodes/Sequence.o

# target to build an object file
Nodes/Sequence.cpp.o:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Nodes/Sequence.cpp.o
.PHONY : Nodes/Sequence.cpp.o

Nodes/Sequence.i: Nodes/Sequence.cpp.i

.PHONY : Nodes/Sequence.i

# target to preprocess a source file
Nodes/Sequence.cpp.i:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Nodes/Sequence.cpp.i
.PHONY : Nodes/Sequence.cpp.i

Nodes/Sequence.s: Nodes/Sequence.cpp.s

.PHONY : Nodes/Sequence.s

# target to generate assembly for a file
Nodes/Sequence.cpp.s:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Nodes/Sequence.cpp.s
.PHONY : Nodes/Sequence.cpp.s

Nodes/SequenceReference.o: Nodes/SequenceReference.cpp.o

.PHONY : Nodes/SequenceReference.o

# target to build an object file
Nodes/SequenceReference.cpp.o:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Nodes/SequenceReference.cpp.o
.PHONY : Nodes/SequenceReference.cpp.o

Nodes/SequenceReference.i: Nodes/SequenceReference.cpp.i

.PHONY : Nodes/SequenceReference.i

# target to preprocess a source file
Nodes/SequenceReference.cpp.i:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Nodes/SequenceReference.cpp.i
.PHONY : Nodes/SequenceReference.cpp.i

Nodes/SequenceReference.s: Nodes/SequenceReference.cpp.s

.PHONY : Nodes/SequenceReference.s

# target to generate assembly for a file
Nodes/SequenceReference.cpp.s:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Nodes/SequenceReference.cpp.s
.PHONY : Nodes/SequenceReference.cpp.s

Nodes/Type.o: Nodes/Type.cpp.o

.PHONY : Nodes/Type.o

# target to build an object file
Nodes/Type.cpp.o:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Nodes/Type.cpp.o
.PHONY : Nodes/Type.cpp.o

Nodes/Type.i: Nodes/Type.cpp.i

.PHONY : Nodes/Type.i

# target to preprocess a source file
Nodes/Type.cpp.i:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Nodes/Type.cpp.i
.PHONY : Nodes/Type.cpp.i

Nodes/Type.s: Nodes/Type.cpp.s

.PHONY : Nodes/Type.s

# target to generate assembly for a file
Nodes/Type.cpp.s:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Nodes/Type.cpp.s
.PHONY : Nodes/Type.cpp.s

Parser.o: Parser.cpp.o

.PHONY : Parser.o

# target to build an object file
Parser.cpp.o:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Parser.cpp.o
.PHONY : Parser.cpp.o

Parser.i: Parser.cpp.i

.PHONY : Parser.i

# target to preprocess a source file
Parser.cpp.i:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Parser.cpp.i
.PHONY : Parser.cpp.i

Parser.s: Parser.cpp.s

.PHONY : Parser.s

# target to generate assembly for a file
Parser.cpp.s:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Parser.cpp.s
.PHONY : Parser.cpp.s

Scanner.o: Scanner.cpp.o

.PHONY : Scanner.o

# target to build an object file
Scanner.cpp.o:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Scanner.cpp.o
.PHONY : Scanner.cpp.o

Scanner.i: Scanner.cpp.i

.PHONY : Scanner.i

# target to preprocess a source file
Scanner.cpp.i:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Scanner.cpp.i
.PHONY : Scanner.cpp.i

Scanner.s: Scanner.cpp.s

.PHONY : Scanner.s

# target to generate assembly for a file
Scanner.cpp.s:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Scanner.cpp.s
.PHONY : Scanner.cpp.s

Source.o: Source.cpp.o

.PHONY : Source.o

# target to build an object file
Source.cpp.o:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Source.cpp.o
.PHONY : Source.cpp.o

Source.i: Source.cpp.i

.PHONY : Source.i

# target to preprocess a source file
Source.cpp.i:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Source.cpp.i
.PHONY : Source.cpp.i

Source.s: Source.cpp.s

.PHONY : Source.s

# target to generate assembly for a file
Source.cpp.s:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/Source.cpp.s
.PHONY : Source.cpp.s

main.o: main.cpp.o

.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i

.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s

.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) -f CMakeFiles/TKOM.dir/build.make CMakeFiles/TKOM.dir/main.cpp.s
.PHONY : main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... TKOM"
	@echo "... Analyzer/AnalyzerField.o"
	@echo "... Analyzer/AnalyzerField.i"
	@echo "... Analyzer/AnalyzerField.s"
	@echo "... Analyzer/AnalyzerPacket.o"
	@echo "... Analyzer/AnalyzerPacket.i"
	@echo "... Analyzer/AnalyzerPacket.s"
	@echo "... Analyzer/PacketsScanner.o"
	@echo "... Analyzer/PacketsScanner.i"
	@echo "... Analyzer/PacketsScanner.s"
	@echo "... Interpreter.o"
	@echo "... Interpreter.i"
	@echo "... Interpreter.s"
	@echo "... Nodes/AltOperation.o"
	@echo "... Nodes/AltOperation.i"
	@echo "... Nodes/AltOperation.s"
	@echo "... Nodes/Block.o"
	@echo "... Nodes/Block.i"
	@echo "... Nodes/Block.s"
	@echo "... Nodes/Expression.o"
	@echo "... Nodes/Expression.i"
	@echo "... Nodes/Expression.s"
	@echo "... Nodes/Field.o"
	@echo "... Nodes/Field.i"
	@echo "... Nodes/Field.s"
	@echo "... Nodes/Packet.o"
	@echo "... Nodes/Packet.i"
	@echo "... Nodes/Packet.s"
	@echo "... Nodes/PacketReference.o"
	@echo "... Nodes/PacketReference.i"
	@echo "... Nodes/PacketReference.s"
	@echo "... Nodes/Protocol.o"
	@echo "... Nodes/Protocol.i"
	@echo "... Nodes/Protocol.s"
	@echo "... Nodes/RepeatOperation.o"
	@echo "... Nodes/RepeatOperation.i"
	@echo "... Nodes/RepeatOperation.s"
	@echo "... Nodes/Sequence.o"
	@echo "... Nodes/Sequence.i"
	@echo "... Nodes/Sequence.s"
	@echo "... Nodes/SequenceReference.o"
	@echo "... Nodes/SequenceReference.i"
	@echo "... Nodes/SequenceReference.s"
	@echo "... Nodes/Type.o"
	@echo "... Nodes/Type.i"
	@echo "... Nodes/Type.s"
	@echo "... Parser.o"
	@echo "... Parser.i"
	@echo "... Parser.s"
	@echo "... Scanner.o"
	@echo "... Scanner.i"
	@echo "... Scanner.s"
	@echo "... Source.o"
	@echo "... Source.i"
	@echo "... Source.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

