all: sfArkXTm

INSTALL?=install

LDLIBS=-lsfark -lz

clean: 
	-rm sfArkXTm

install: sfArkXTm
	$(INSTALL) -D sfArkXTm $(DESTDIR)/usr/local/bin/sfArkXTm
