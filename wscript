#!/usr/bin/env python

APPNAME = "umbra"
VERSION = "0.1.0"

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

"""
- The build order is ext -> src -> lib
- external/internal libraries must be added before configure, because
  configure must take them into account.

Options:
- (!) configure
- (C) build
- (C) clean
- (.) dist
- (B) install
- (B) uninstall
- *(.) info

Flags:
	-b --build-mode {debug|release}
	-T --toolkit    <tkname>
	-A --arch       <archname>
	-P --platform   <arch>-<system|compiler>-<build-mode>-<features...>
	-S --system     <sysname>
	-x --feature    <feat1>[,<feat2>[,...]]
	-e --env        k=v
	-d --def        k=v
	   --sites
	-s --site       <site1>[,<site2>[,...]]  
"""

defaults = {
	'build_mode' : 'debug'
	, 'compiler' : 'default'
	, 'arch'     : 'x86'
	, 'system'   : 'native'
	, 'features' : ''
}

build_modes = ['debug', 'release']
compilers = ['default', 'gcc', 'msvc']
architectures = ['x86', 'x86_64']
systems = ['ansi']
sites = [
	{
		'name'    : 'ext'
		, 'dir'   : 'ext'
		, 'desc'  : 'Folder containing '
		, 'files' : 'win32:win32/** *:*'
	}
]

#==============================================================================
def options(ctx):
	"""Adds options to the script.
	"""
	ctx.load('compiler_c compiler_cxx')
	
	ctx.add_option('-b', '--build-mode',
		action = 'store',
		dest = 'build_mode',
		type = 'choice',
		choices = build_modes,
		default = 'release',
		help = 
			"Sets the build mode.\n" + 
			"For a list of available build modes,\n" +
			"run `waf info --build-modes`.")
	
	ctx.add_option('-C', '--compiler',
		action = 'store',
		dest = 'compiler_name',
		type = 'choice',
		choices = compilers,
		default = 'default',
		help = "Chooses the compiler used to build the library.")
	
	ctx.add_option('-P', '--platform',
		action = 'store',
		dest = 'platform_name',
		default = '',
		type = 'string',
		help = 
			"Selects the target platform (for cross\n" + 
			"compilation or for merely using\n" + 
			"different options). For a list of supported\n" + 
			"platforms, run `waf info --platforms`")
	
	ctx.add_option('-F', '--feature',
		action = 'append',
		type = 'string',
		dest = 'features_list',
		help =  
			"Adds features to the configure/build session.\n"
			"Features must be added at configure time. Availability\n"
			"of those features are dependent on the development\n"
			"environment. Some modules may enforce their use or\n"
			"silently ignore them.\n"
			"For a general list of supported features, run\n"
			"`waf info --features`. For a list of feature support\n"
			"per module, run `waf info --modules`.")
	
	ctx.add_option('--platforms',
		action = 'store_true',
		dest = 'use_platforms',
		default = True,
		help = "Flag used to list the supported platforms.")
	
	ctx.add_option('--build-modes',
		action = 'store_true',
		dest = 'use_build_modes',
		default = False,
		help = "Flag used to list build modes.")
	
	ctx.add_option('--features',
		action = 'store_true',
		dest = 'use_features',
		default = False,
		help = "Flag used to list globally-recognized features.")
	
	ctx.add_option('--compilers',
		action = 'store_true',
		dest = 'use_compilers',
		default = False,
		help = "Flag used to list all supported compilers.")
	
	ctx.add_option('-e', '--env',
		action = 'append',
		dest = 'env_flags',
		help = "Used to insert values into 'ctx.env'.\n" +
			"Note, however, that values inserted this way\n" +
			"are NOT meant to be persistent!")
	

def configure(ctx):		
	if ctx.options.build_mode == "debug":
		ctx.env.DEBUG = 1
	
	if ctx.options.features_list:
		if "static" in ctx.options.features_list:
			ctx.env.STATIC = 1
		
		if "wide" in ctx.options.features_list:
			ctx.env.WIDE = 1
	
	compiler_name = ctx.options.compiler_name
	if "msvc" == compiler_name:
		ctx.load('msvc')
	elif "gcc" == compiler_name:
		ctx.load('gcc')
		ctx.load('g++')
	else:
		ctx.load('compiler_c compiler_cxx')
	
	ctx.recurse(ext)
	ctx.recurse(inc)
	ctx.recurse(src)
	ctx.recurse(lib)
	ctx.recurse(doc)
	ctx.recurse(tst)

def build(ctx):
	ctx.recurse(ext)
	ctx.recurse(inc)
	ctx.recurse(src)
	ctx.recurse(lib)
	ctx.recurse(doc)
	
	# Test won't be recursed here, to leave the user to choose when to run
	# the tests, because they may take time to finish. 
	#ctx.recurse(tst)




