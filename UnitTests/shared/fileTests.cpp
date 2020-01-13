#include "CppUnitTest.h"

#include "../../Advent2019/shared/types.h"
#include "../../Advent2019/shared/file.hpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(fileTests)
	{
	public:
		
		TEST_METHOD(readAllTextTest)
		{
			const char* expected = "R75,D30,R83,U83,L12,D49,R71,U7,L72\r\nU62,R66,U55,R34,D71,R55,D58,R83";

			const char* filepath = "C:\\Users\\Robert\\Documents\\Advent2019\\UnitTests\\input\\day01test.txt";
			s32 size;
			const char* result = ReadAllText(filepath, &size);

			Assert::AreEqual(expected, result);
		}
	};
}
