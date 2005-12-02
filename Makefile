#----------------------------------------------------------------
#
#  Globales Makefile
#
#  IgH EtherCAT-Treiber
#
#  $Id$
#
#----------------------------------------------------------------

CONFIG_FILE = ethercat.conf

ifeq ($(CONFIG_FILE),$(wildcard $(CONFIG_FILE)))
include $(CONFIG_FILE)
endif

#----------------------------------------------------------------

all: .drivers .rt .mini

doc docs:
	doxygen Doxyfile

.drivers:
	$(MAKE) -C drivers

ifeq ($(MAKE_RT),yes)
.rt:
	$(MAKE) -C rt
else
.rt:
	@echo "Skipping Real-Time."
endif

.mini:
	$(MAKE) -C mini

config conf $(CONFIG_FILE):
	@echo "# EtherCAT Konfigurationsdatei Kernel 2.6" > $(CONFIG_FILE)
	@echo >> $(CONFIG_FILE)
	@echo "KERNELDIR = /usr/src/linux" >> $(CONFIG_FILE)
	@echo "RTAIDIR   =" >> $(CONFIG_FILE)
	@echo "RTLIBDIR  =" >> $(CONFIG_FILE)
	@echo >> $(CONFIG_FILE)
	@echo "MAKE_RT    = yes" >> $(CONFIG_FILE)
	@echo >> $(CONFIG_FILE)
	@echo "$(CONFIG_FILE) erstellt."

clean:
	$(MAKE) -C rt clean
	$(MAKE) -C drivers clean
	$(MAKE) -C mini clean

#----------------------------------------------------------------
