CC              := gcc
CXXFLAGS 		:= -std=c++17 -Wall -Werror -Wextra -Wshadow -Wconversion
CXX_NO_EXTRA_FLAGS := -std=c++17
CXXCOV 			:= --coverage -g
SOURCES = \
				tests/set_tests.cc \
				tests/multiset_tests.cc \
				tests/tests.cc

all: test

test: clean
	${CC} ${CXXFLAGS} ${CXXCOV} $(SOURCES) -lgtest -lstdc++ -lm  -o test.out
	./test.out
	@make clean
	
test_no_flags: clean
	${CC} ${CXX_NO_EXTRA_FLAGS} ${CXXCOV} $(SOURCES) -lgtest -lstdc++ -lm  -o test.out
	./test.out
	@make clean

valgrind: clean
	${CC} ${CXXFLAGS} ${CXXCOV} $(SOURCES) -lgtest -lstdc++ -lm -o test.out
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.log ./test.out

gcov_report: clean
	${CC} ${CXXFLAGS} ${CXXCOV} $(SOURCES) -lgtest -lstdc++ -lm -o test_cov.out
	./test_cov.out
	lcov -t "containers" -o containers.info --ignore-errors mismatch,inconsistent --no-external -c -d .
	make clean_gcov
	genhtml -o report containers.info
	open report/index.html

cppcheck:
	@find .. -type f -name "*.cc" -exec cppcheck --enable=all --suppress=missingIncludeSystem --language=c++ --std=c++17 {} \;
	@find .. -type f -name "*.c" -exec cppcheck --enable=all --suppress=missingIncludeSystem --language=c++ --std=c++17 {} \;
	@find .. -type f -name "*.h" -exec cppcheck --enable=all --suppress=missingIncludeSystem --language=c++ --std=c++17 {} \;
	@echo "Cppcheck is finished"

clean: clean_project clean_static_lib clean_log clean_exec clean_obj clean_gcov clean_lcov clean_lcov_report
	@echo "Clean finished"

clean_project:

clean_after_building:
	@rm -rf ${OBJ_DIR}
clean_static_lib:
	@find .. -type f -name "*.a" -exec rm {} \;
clean_log:
	@find .. -type f -name "*.log" -exec rm {} \;
clean_exec:
	@find .. -type f -name "*.out" -exec rm {} \;
clean_obj:
	@find .. -type f -name "*.o" -exec rm {} \;
clean_gcov:
	@find .. -type f -name "*.gcda" -exec rm {} \;
	@find .. -type f -name "*.gcno" -exec rm {} \;
clean_lcov:
	@find .. -type f -name "*.info" -exec rm {} \;
clean_lcov_report:
	@rm -rf report
