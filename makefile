all:
	tcc -O3 cmpb.c -o cmpb
install: cmpb
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f cmpb $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/cmpb
	@echo cmpb installed sucsessfully!

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/cmpb
