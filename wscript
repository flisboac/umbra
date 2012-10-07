#!/usr/bin/env python

import waflib

MAJOR = 0
MINOR = 1
PATCH = 0
VENDOR = ""
APPNAME = "umbra"
VERSION = "%d.%d.%d" % (MAJOR, MINOR, PATCH)

# Top of the source tree
top = '.'
# Where build will take place
bld = 'build'
out = bld

# This list is in the correct recursion order.
ext = 'ext'     # Where all external libraries and tools live
inc = 'include' # Umbra's include files
src = 'src'     # Umbra's sources, where all subsystems are held
lib = 'lib'     # Umbra libraries
doc = 'doc'     # documentation config files
tst = 'test'    # Unit tests


#==============================================================================
def options(ctx):
	ctx.gmodule = waflib.Context.g_module
	ctx.load('compiler_c compiler_cxx')
	#ctx.recurse(ext)
	#ctx.recurse(inc)
	#ctx.recurse(src)
	#ctx.recurse(lib)
	#ctx.recurse(doc)
	#ctx.recurse(tst)
	

def info(ctx):
	"""Shows information about modules and the build process."""
	ctx.gmodule = waflib.Context.g_module
	ctx.recurse(ext)
	ctx.recurse(inc)
	ctx.recurse(src)
	ctx.recurse(lib)
	ctx.recurse(doc)
	ctx.recurse(tst)


def configure(ctx):
	ctx.load('compiler_c compiler_cxx')
	ctx.gmodule = waflib.Context.g_module
	ctx.recurse(ext)
	ctx.recurse(inc)
	ctx.recurse(src)
	ctx.recurse(lib)
	ctx.recurse(doc)
	ctx.recurse(tst)


def build(ctx):
	ctx.gmodule = waflib.Context.g_module
	ctx.recurse(ext)
	ctx.recurse(inc)
	ctx.recurse(src)
	ctx.recurse(lib)
	ctx.recurse(doc)
	
	# Test won't be recursed here, to leave the user to choose when to run
	# the tests, because they may take time to finish. 
	#ctx.recurse(tst)

def test(ctx):
	ctx.gmodule = waflib.Context.g_module
	ctx.recurse(tst)


class Test(waflib.Build.BuildContext):
	cmd = 'test'
	fun = 'test'
