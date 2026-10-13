FILE = q1

all: $(FILE)

$(FILE): $(FILE).o
	g++ -Wall -g -o $(FILE) $(FILE).o

$(FILE).o: $(FILE).cpp
	g++ -Wall -g -c $(FILE).cpp

run: $(FILE)
	./$(FILE)

clean:
	rm -f $(FILE).o $(FILE)

.PHONY: all run clean