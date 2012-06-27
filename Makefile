debug:
	make -f Makefile.osx Debug
	cd bin/MindPaint_debug.app/Contents/MacOS && ./MindPaint_debug

release:
	make -f Makefile.osx

clean:
	make -f Makefile.osx Clean