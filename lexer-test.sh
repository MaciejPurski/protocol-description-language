#!/bin/bash

for f in tests/*; do
	echo "------Begin test: $f------"
	./cmake-build-debug/TKOM --lexer-test $f
	echo "--------------------------"
	echo ""
done