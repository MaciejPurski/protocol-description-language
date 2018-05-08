import sys
import importlib

if len(sys.argv) != 2:
	print("Wrong argument format. Expected: generator <file_def_name>")
	exit(0)


print("importing module: " + sys.argv[1])
importlib.import_module(sys.argv[1])