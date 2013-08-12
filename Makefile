all: sfarkxtc

INSTALL?=install

LDLIBS=-lsfark -lz

clean: 
	-rm sfarkxtc 2>/dev/null || true

install: sfarkxtc
	$(INSTALL) -D sfarkxtc $(DESTDIR)/usr/local/bin/sfarkxtc
