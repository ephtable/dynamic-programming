CC     = gcc -std=c99
DEBUG  = -Wall -g

CFLAGS = `pkg-config --cflags --libs glib-2.0` -lm
GFLAGS = `pkg-config --cflags --libs gtk+-3.0 gmodule-export-2.0` -lm

COMMON = -Isrc/main/ src/main/matrix.c src/main/utils.c src/main/latex.c src/main/graphviz.c
GUICOMMON = src/main/dialogs.c

# Rules
all: clean bin/main bin/floyd bin/knapsack bin/optbst bin/probwin bin/replacement

test: clean bin/test/floyd bin/test/knapsack bin/test/optbst bin/test/probwin bin/test/replacement

# Algorithms
floyd: clean bin/floyd bin/test/floyd
knapsack: clean bin/knapsack bin/test/knapsack
optbst: clean bin/optbst bin/test/optbst
probwin: clean bin/probwin bin/test/probwin
replacement: clean bin/replacement bin/test/replacement

# Main binaries
bin/main: src/main/main.c
	$(CC) $(DEBUG) -o $@ $? $(COMMON) $(GUICOMMON) $(GFLAGS)

bin/floyd: src/floyd/main.c src/floyd/floyd.c src/floyd/report.c
	$(CC) $(DEBUG) -o $@ $? $(COMMON) $(GUICOMMON) $(GFLAGS)

bin/knapsack: src/knapsack/main.c src/knapsack/knapsack.c src/knapsack/report.c
	$(CC) $(DEBUG) -o $@ $? $(COMMON) $(GUICOMMON) $(GFLAGS)

bin/optbst: src/optbst/main.c src/optbst/optbst.c src/optbst/report.c
	$(CC) $(DEBUG) -o $@ $? $(COMMON) $(GUICOMMON) $(GFLAGS)

bin/probwin: src/probwin/main.c src/probwin/probwin.c src/probwin/report.c
	$(CC) $(DEBUG) -o $@ $? $(COMMON) $(GUICOMMON) $(GFLAGS)

bin/replacement: src/replacement/main.c src/replacement/replacement.c src/replacement/report.c
	$(CC) $(DEBUG) -o $@ $? $(COMMON) $(GUICOMMON) $(GFLAGS)


# Test binaries
bin/test/floyd: src/floyd/test.c src/floyd/floyd.c src/floyd/report.c
	$(CC) $(DEBUG) -o $@ $? $(COMMON) $(CFLAGS)

bin/test/knapsack: src/knapsack/test.c src/knapsack/knapsack.c src/knapsack/report.c
	$(CC) $(DEBUG) -o $@ $? $(COMMON) $(CFLAGS)

bin/test/optbst: src/optbst/test.c src/optbst/optbst.c src/optbst/report.c
	$(CC) $(DEBUG) -o $@ $? $(COMMON) $(CFLAGS)

bin/test/probwin: src/probwin/test.c src/probwin/probwin.c src/probwin/report.c
	$(CC) $(DEBUG) -o $@ $? $(COMMON) $(CFLAGS)

bin/test/replacement: src/replacement/test.c src/replacement/replacement.c src/replacement/report.c
	$(CC) $(DEBUG) -o $@ $? $(COMMON) $(CFLAGS)


# Clean
clean:
	rm -f `find bin/ -executable -type f`
	rm -f `find bin/test/ -executable -type f`
	rm -f reports/floyd.*
	rm -f reports/graph.*
	rm -f reports/knapsack.*
	rm -f reports/optbst.*
	rm -f reports/tree.*
	rm -f reports/probwin.*
	rm -f reports/replacement.*
