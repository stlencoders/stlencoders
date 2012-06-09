# Process this file with automake to produce Makefile.in

#ACLOCAL_AMFLAGS = -I m4

SUBDIRS = doc src include tests

EXTRA_DIST = stlencoders.sln stlencoders.props

docdistdir = $(PACKAGE)-doc-$(VERSION)

docdistdir:
	$(MKDIR_P) $(docdistdir)
	$(MAKE) $(AM_MAKEFLAGS) docdir="`pwd`/$(docdistdir)" install-html

docdist-gzip: docdistdir
	$(AMTAR) chof - $(docdistdir) | gzip -c >$(docdistdir).tar.gz
	rm -rf $(docdistdir)

docdist-zip: docdistdir
	-rm -f $(docdistdir).zip
	zip -rq $(docdistdir).zip $(docdistdir)
	rm -rf $(docdistdir)

.PHONY: docdistdir docdist docdist-gzip docdist-zip
