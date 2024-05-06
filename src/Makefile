CXX = gcc
CXX = g++
CXX_FLAGS = -Wall -Werror -Wextra -g -std=c++17
CFLAGS = -Wall -Werror -Wextra -g -std=c11
GCOV_FLAGS = --coverage
LDLIBS = -lgtest
QMAKE5 = qmake

SHELL = /bin/sh

MODEL = ./model/model.a
MODEL_FLAGS = -L. -l:$(MODEL)
MODEL_SOURCES = $(wildcard ./model/*.cc)
MODEL_OBJECTS = $(MODEL_SOURCES:.cc=.o)

TEST = tests/tests
TEST_SOURCES = tests/main.cc
TEST_OBJECTS = $(TEST_SOURCES:.cc=.o)

CHECK = ./check/include.check $(wildcard ./check/t_*)

all: model

install: clean build
	-mkdir ../SmartCalc_v2.0
	cp -rf ../build/qt ../SmartCalc_v2.0/

run:
	./../SmartCalc_v2.0/qt

build: clean
	-mkdir ../build
	cd ../build; $(QMAKE5) ../src/view/qt/qt.pro
	cd ../build; pwd; make -C . 2> /dev/null 1> /dev/null

uninstall:
	rm -rf ../SmartCalc_v2.0

clean:
	rm -f model/model.a model/*.o model/*.gcno model/*.gcda model.info
	rm -f tests/tests tests/*.o tests/*.gcno tests/*.gcda
	rm -fr report
	rm -fr ../build
	rm -fr ../SmartCalc_v2.0
	rm -f valgrind.log

dvi:
	open ./dvi.html

dist: clean
	cd ./view/qt; $(QMAKE5) qt.pro
	cd ./view/qt; make dist
	-mkdir ../build
	mv -f ./view/qt/qt1.0.0.tar.gz ../build/

gcov_report: test
	lcov -t "$(TEST)" -o model.info -c -d .
	genhtml -o report model.info
	open ./report/index.html

test: test_build test_run

$(MODEL) : $(MODEL_OBJECTS)
	@echo model
	ar r $(MODEL) $(MODEL_OBJECTS)

test_build : $(MODEL) $(TEST_OBJECTS)
	$(CXX) -g $(GCOV_FLAGS) -o $(TEST) $(TEST_OBJECTS) $(MODEL_FLAGS) $(LDLIBS)

test_run:
	./$(TEST)

leak: test_build
	#rm -f valgrind.log
	valgrind --tool=memcheck \
		     --leak-check=full \
		     --show-leak-kinds=all \
		     --num-callers=20 \
		     --track-origins=yes \
		     --log-file=valgrind.log \
		     ./$(TEST) --gtest_brief=1


style :
	clang-format -style=Google -n ./model/*.cc tests/main.cc view/qt/*.cc

style_fix :
	clang-format -style=Google -i ./model/*.cc tests/main.cc view/qt/*.cc


%.o : %.cc
	$(CXX) $(CXX_FLAGS) $(GCOV_FLAGS) -c $< -o $@


