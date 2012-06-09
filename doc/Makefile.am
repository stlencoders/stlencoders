# Process this file with automake to produce Makefile.in

EXTRA_DIST = Doxymain

html-local:
	$(DOXYGEN) Doxyfile

install-html-local: html-local
	$(MKDIR_P) $(DESTDIR)$(htmldir)
	$(INSTALL_DATA) html/*.* $(DESTDIR)$(htmldir)

clean-local:
	rm -rf html
