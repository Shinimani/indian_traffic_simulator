Compiler = g++
Deps = headers
mainIn = code_file/*.cpp


main:$(mainIn)
	@$(Compiler) -o main.out -I $(Deps)/ $(mainIn) -lGL -lGLU -lglut -lm