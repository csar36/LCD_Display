CC=g++
FLAGS=-Wall -Wextra -Wno-unused -std=c++11 -pedantic
OBJS=stdafx.o gpio.o LCD_Display.o easylogging++.o Timer.o
OUT=LCD_Display

$(OUT): $(OBJS) main.cpp
	$(CC) $(FLAGS) $^ -o $@

%.o: %.cpp %.h
	$(CC) $(FLAGS) -c $<  -o $@

clean:
	rm -f $(OUT)
	rm -f *.o

.PHONY: clean
