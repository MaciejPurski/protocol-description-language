cmake_minimum_required(VERSION 3.9)
project(protocol-description-language)

set(CMAKE_CXX_STANDARD 17)

add_executable(TKOM main.cpp Source.cpp Source.h Scanner.cpp Scanner.h Token.h LexerTest.h Parser.cpp Parser.h Protocol.cpp Protocol.h Sequence.cpp Sequence.h Block.h Operation.h RepeatOperation.h AltOperation.h SequenceReference.cpp SequenceReference.h PacketReference.cpp PacketReference.h ParserTest.h Node.h Block.cpp Packet.cpp Packet.h AltOperation.cpp RepeatOperation.cpp Field.cpp Field.h Type.cpp Type.h Expression.cpp Expression.h Reference.h)