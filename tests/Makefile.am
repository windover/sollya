EXTRA_DIST= check.sollya checkTMandAD.sollya check.sollya.output timecheck.sollya timecheck.sollya.output check.proto

TESTS_ENVIRONMENT=$(SHELL) 
TESTS= check.sh 

TESTFILES= check.sollya timecheck.sollya

.PHONY: $(top_builddir)/sollya

$(top_builddir)/sollya:
	cd $(top_builddir); make all


check.sh: $(top_builddir)/sollya check.proto $(TESTFILES)
	echo "#!/bin/sh" > check.sh
	echo "SOLLYA="$(top_builddir)"/sollya" >> check.sh
	echo "TESTFILES=\""$(TESTFILES)"\"" >> check.sh
	cat check.proto >> check.sh
	chmod +x check.sh






