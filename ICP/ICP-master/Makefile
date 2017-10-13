#
# ICP 2016 Makefie
#

export PATH:=/usr/local/share/Qt-5.5.1/5.5/gcc_64/bin:${PATH}
export LD_LIBRARY_PATH=/usr/local/share/Qt-5.5.1/5.5/gcc_64/lib
export QT_PLUGIN_PATH=/usr/local/share/Qt-5.5.1/5.5/gcc_64

ifneq ("$(wildcard /usr/bin/qmake-qt5)","")
QMAKE = "qmake-qt5"
else
QMAKE = "qmake"
endif
ifneq ("$(wildcard /usr/local/share/Qt-5.5.1/5.5/gcc_64/bin/qmake)","")
QMAKE = "/usr/local/share/Qt-5.5.1/5.5/gcc_64/bin/qmake"
endif

# make all
all: gui cli

#make gui
gui:
		@cd src && $(QMAKE) -o Makefile && make
		mv src/Othello ./hra2016

#make cli
cli:
		g++ -std=c++11 src/cli.cpp src/board.cpp src/stone.cpp -o hra2016-cli

#run both
run: all
		./hra2016
		./hra2016-cli

#run gui
rungui: gui
		./hra2016

#generate doc
doxygen:
		-mkdir doc
		doxygen src/doxygen.conf

#zip
pack: clean
		zip xjochl00.zip Makefile src/* src/img/* doc examples src LICENSE.txt README.txt qt.conf savegame.dat

#clean
clean:
		rm src/*.o	-rf
		rm src/Makefile	-rf
		rm hra2016	-rf
		rm hra2016-cli	-rf
		rm doc/*	-rf
		rm -rf xjochl00.zip