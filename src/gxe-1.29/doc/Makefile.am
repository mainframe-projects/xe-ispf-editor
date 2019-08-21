## Process this file with automake to produce Makefile.in

HTMLDIR = xehelp
PIXMAPDIR=$(PACKAGE_PIXMAPS_DIR)
TARGET_DIR=$(PACKAGE_HELP_DIR)
TARGET_HTML_DIR=$(DESTDIR)$(TARGET_DIR)/$(HTMLDIR)
TARGET_PIXMAP_DIR=$(DESTDIR)$(PIXMAPDIR)
SOURCE_HTML_DIR = $(srcdir)/$(HTMLDIR)
SOURCE_PIXMAP_DIR = $(srcdir)/$(HTMLDIR)
EXTRA_DIST = \
	en \
	ja \
	xehelp

install-data-local:
	@echo '-- Installing $(SOURCE_HTML_DIR) to $(TARGET_HTML_DIR)'
	$(INSTALL_DATA) -m 755 -d $(DESTDIR)$(TARGET_DIR)
	$(INSTALL_DATA) -m 755 -d $(TARGET_HTML_DIR)
	$(INSTALL_DATA) -m 755 -d $(TARGET_PIXMAP_DIR)
	cp -pR $(SOURCE_HTML_DIR)/*   $(TARGET_HTML_DIR)
	cp -p  $(SOURCE_PIXMAP_DIR)/wxe.png  $(TARGET_PIXMAP_DIR)
uninstall-local:
	rm -fr $(DESTDIR)$(TARGET_DIR)
	rm -fr $(TARGET_PIXMAP_DIR)
