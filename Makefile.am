# Process this file with automake to produce Makefile.in

docdistdir = $(PACKAGE)-doc-$(VERSION)

SUBDIRS = doc src include tests

EXTRA_DIST = \
	debian/changelog debian/compat debian/control debian/copyright \
	debian/libstlencoders-bin.install \
	debian/libstlencoders-dev.examples \
	debian/libstlencoders-dev.install \
	debian/libstlencoders-doc.docs \
	debian/rules \
	stlencoders.sln stlencoders.props

dist-deb:
	$(DPKG_BUILDPACKAGE) -b -uc
	$(MAKE) -f debian/rules clean

dist-doc:
	$(MKDIR_P) $(docdistdir)
	$(MAKE) $(AM_MAKEFLAGS) docdir="`pwd`/$(docdistdir)" install-html
	zip -rq $(docdistdir).zip $(docdistdir)
	rm -rf $(docdistdir)

.PHONY: dist-deb dist-doc
