# Process this file with automake to produce Makefile.in

ACLOCAL_AMFLAGS = -I m4

SUBDIRS = src include tests

EXTRA_DIST = Doxymain stlencoders.sln stlencoders.props

if HAVE_DOXYGEN

doc:
	$(DOXYGEN) Doxyfile

docdist = $(PACKAGE)-doc-$(VERSION)

docdistdir: distdir
	(cd $(distdir) && ./configure && make doc)

docdist-gzip: docdistdir
	$(AMTAR) chof - $(distdir)/doc | gzip -c >$(docdist).tar.gz
	rm -rf $(distdir)

docdist-zip: docdistdir
	-rm -f $(docdist).zip
	zip -rq $(docdist).zip $(distdir)/doc
	rm -rf $(distdir)

clean-local:
	rm -rf doc

.PHONY: doc docdistdir docdist docdist-gzip docdist-zip

endif
