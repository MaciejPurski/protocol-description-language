cmake_minimum_required(VERSION 3.9)
project(protocol-description-language)

set(CMAKE_CXX_STANDARD 17)

add_executable(TKOM main.cpp Source.cpp Source.h Scanner.cpp Scanner.h Token.h LexerTest.h Parser.cpp Parser.h
        Nodes/Protocol.cpp Nodes/Protocol.h Nodes/Sequence.cpp Nodes/Sequence.h Nodes/Block.h Nodes/Operation.h Nodes/RepeatOperation.h Nodes/AltOperation.h
        Nodes/SequenceReference.cpp Nodes/SequenceReference.h Nodes/PacketReference.cpp Nodes/PacketReference.h ParserTest.h Nodes/Node.h Nodes/Block.cpp
        Nodes/Packet.cpp Nodes/Packet.h Nodes/AltOperation.cpp Nodes/RepeatOperation.cpp Nodes/Field.cpp Nodes/Field.h Nodes/Type.cpp Nodes/Type.h Nodes/Expression.cpp
        Nodes/Expression.h Nodes/Reference.h Interpreter.cpp Interpreter.h Analyzer/AnalyzerPacket.cpp Analyzer/AnalyzerPacket.h Analyzer/AnalyzerField.cpp Analyzer/AnalyzerField.h Analyzer/PacketsParser.cpp Analyzer/PacketsParser.h Analyzer/SequenceParser.cpp Analyzer/SequenceParser.h)