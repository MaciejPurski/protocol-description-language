#!/bin/bash

for f in tests/*; do
	echo "------Begin test: $f------"
	./TKOM --lexer-test $f
	echo "--------------------------"
	echo ""
done