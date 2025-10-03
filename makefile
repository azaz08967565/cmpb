all:
	gcc -O3 cpb.c -o cpb
install: cpb
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f cpb $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/cpb
	@echo cpb installed sucsessfully!

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/cpb
