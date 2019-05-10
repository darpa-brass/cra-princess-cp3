CC=gcc -O3 -fno-stack-protector -march=native -mtune=native 

data_generator: data_generator.o metric_calculator.o transformed_pathplanner.o main.o
	${CC} -o data_generator data_generator.o metric_calculator.o transformed_pathplanner.o main.o -lm
clean:
	rm data_generator *.o

