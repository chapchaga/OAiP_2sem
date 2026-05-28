TEMPLATE = subdirs
SUBDIRS = StringLib StringApp StringTests

StringApp.depends = StringLib
StringTests.depends = StringLib
