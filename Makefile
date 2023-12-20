COMPLR = gcc
CFLAGS = -Wall -Wextra -g
SRCDIR = lib
INCDIR = header_files
BINDIR = bin
TARGET = diary
DEPEND = -L. -lncursesw
# Every additional line in this file \
	drives me closer to suicide, \
	assuming that line isn't a \
	comment like these ones are.

SOURCES := main.c $(wildcard $(SRCDIR)/*.c)
HEADERS := $(wildcard $(INCDIR)/*.h)
OBJECTS := $(SOURCES:.c=.o)

$(BINDIR)/$(TARGET): $(OBJECTS)
	@mkdir $(BINDIR)
	$(COMPLR) $(CFLAGS) -I$(INCDIR) $^ -o $@ $(DEPEND) 
	@echo "Executable created: $(BINDIR)/$(TARGET)"

%.o: %.c $(HEADERS)
	$(COMPLR) $(CFLAGS) -I$(INCDIR) -c $< -o $@ $(DEPEND)

run:
	.\$(BINDIR)\$(TARGET).exe

clean:
	del "$(SRCDIR)\*.o"
	del "*.o"
	rd /s /q "$(BINDIR)"
	@echo "Cleaned up the mess."

.PHONY: clean