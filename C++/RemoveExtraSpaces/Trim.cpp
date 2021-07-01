#include <iostream>
#include <chrono>
#include <boost/algorithm/string/trim_all.hpp>

#include "Trim.h"

void tests()
{
	std::cout << "TEST1:" << std::endl;
	std::string test1 = "              On my   home world       ";
	std::string test11 = test1;
	trimAll(test1);
	boost::algorithm::trim_all(test11);
	std::cout << "RESULT:" << std::endl << test1 << std::endl;
	if (test1 == test11) {
		std::cout << "TEST1 PASSED" << std::endl << test1 << std::endl;;
	}
	else {
		std::cout << "TEST1 FAILED" << std::endl << test1 << std::endl;;
	}

	std::cout << "TEST2:" << std::endl;
	std::string test2 = "On my   home world       ";
	std::string test22 = test2;
	trimAll(test2);
	boost::algorithm::trim_all(test22);
	std::cout << "RESULT:" << std::endl << test2 << std::endl;
	if (test2 == test22) {
		std::cout << "TEST2 PASSED" << std::endl << test2 << std::endl;;
	}
	else {
		std::cout << "TEST2 FAILED" << std::endl << test2 << std::endl;;
	}

	std::cout << "TEST3:" << std::endl;
	std::string test3 = " On  my   home    world     ";
	std::string test33 = test3;
	trimAll(test3);
	boost::algorithm::trim_all(test33);
	std::cout << "RESULT:" << std::endl << test3 << std::endl;;
	if (test3 == test33) {
		std::cout << "TEST3 PASSED" << std::endl << test3 << std::endl;;
	}
	else {
		std::cout << "TEST3 FAILED" << std::endl << test3 << std::endl;;
	}

	std::cout << "TEST4:" << std::endl;
	std::string test4;
	std::string test44 = test4;
	trimAll(test4);
	boost::algorithm::trim_all(test44);
	std::cout << "RESULT:" << std::endl << test4 << std::endl;;
	if (test4 == test44) {
		std::cout << "TEST4 PASSED" << std::endl << test4 << std::endl;;
	}
	else {
		std::cout << "TEST4 FAILED" << std::endl << test4 << std::endl;;
	}

	std::cout << "TEST5:" << std::endl;
	std::string test5 = " ";
	std::string test55 = test5;
	trimAll(test5);
	boost::algorithm::trim_all(test55);
	std::cout << "RESULT:" << std::endl << test5 << std::endl;;
	if (test5 == test55) {
		std::cout << "TEST5 PASSED" << std::endl << test5 << std::endl;;
	}
	else {
		std::cout << "TEST5 FAILED" << std::endl << test5 << std::endl;;
	}


	using std::chrono::high_resolution_clock;
	using std::chrono::duration;
	using std::chrono::milliseconds;

	std::cout << "TEST6:" << std::endl;
	std::string test6(1000000, ' ');
	test6.insert(0, "  begin");
	test6.append("end  ");
	std::string test66 = test6;

	auto t1 = high_resolution_clock::now();
	trimAll(test6);
	auto t2 = high_resolution_clock::now();
	duration<double, std::milli> ms = t2 - t1;
	std::cout << "Time execution (my): " << ms.count() << "ms" << std::endl;

	t1 = high_resolution_clock::now();
	boost::algorithm::trim_all(test66);
	t2 = high_resolution_clock::now();
	ms = t2 - t1;
	std::cout << "Time execution (boost): " << ms.count() << "ms" << std::endl;

	std::cout << "RESULT:" << std::endl << test6 << std::endl;;
	if (test6 == test66) {
		std::cout << "TEST6 PASSED" << std::endl << test6 << std::endl;;
	}
	else {
		std::cout << "TEST6 FAILED" << std::endl << test6 << std::endl;;
	}

	std::cout << "TEST7:" << std::endl;
	std::wstring test7;
	std::wstring test77 = test7;
	trimAll(test7);
	boost::algorithm::trim_all(test77);
	std::wcout << "RESULT:" << std::endl << test7 << std::endl;;
	if (test5 == test55) {
		std::wcout << "TEST5 PASSED" << std::endl << test7 << std::endl;;
	}
	else {
		std::wcout << "TEST5 FAILED" << std::endl << test7 << std::endl;;
	}
}

int main()
{
	tests();

	return 0;
}