# Attempt to load a config.make file.
# If none is found, project defaults in config.project.make will be used.
ifneq ($(wildcard config.make),)
	include config.make
endif

Foo=newdir
.PHONY: print_vars
print_vars:
	echo $(Foo)

# make sure the the OF_ROOT location is defined
ifndef OF_ROOT
    OF_ROOT=$(realpath ../../..)
endif
OF_ROOT=/Users/srishti/Documents/of_v0.10.1_osx_release
# call the project makefile!
include $(OF_ROOT)/libs/openFrameworksCompiled/project/makefileCommon/compile.project.mk
