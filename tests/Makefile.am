EXTRA_DIST= check.sollya check.sollya.output check.proto

TESTS_ENVIRONMENT=$(SHELL) 
TESTS= check.sh 

TESTFILES= check.sollya 

check.sh: $(top_builddir)/sollya check.proto $(TESTFILES)
	echo "#!/bin/sh" > check.sh
	echo "SOLLYA="$(top_builddir)"/sollya" >> check.sh
	echo "TESTFILES=\""$(TESTFILES)"\"" >> check.sh
	cat check.proto >> check.sh
	chmod +x check.sh






