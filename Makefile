CC     = c99
DEBUG  = -Wall -g

CFLAGS = `pkg-config --cflags --libs glib-2.0`
GFLAGS = `pkg-config --cflags --libs gtk+-3.0 gmodule-export-2.0`

COMMON = -Isrc/main/ src/main/matrix.c src/main/utils.c

all: bin/main bin/floyd bin/knapsack
#bin/optbst bin/probwin bin/replacement

bin/main: src/main/main.c
	$(CC) $(DEBUG) -o $@ $< $(COMMON) $(GFLAGS)

bin/floyd: src/floyd/main.c src/floyd/floyd.h src/floyd/floyd.c
	$(CC) $(DEBUG) -o $@ $< $(COMMON) $(GFLAGS)

bin/knapsack: src/knapsack/main.c src/knapsack/knapsack.h src/knapsack/knapsack.c
	$(CC) $(DEBUG) -o $@ $< $(COMMON) $(GFLAGS)

clean:
	rm -f bin/*

