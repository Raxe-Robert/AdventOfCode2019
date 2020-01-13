#include "CppUnitTest.h"

#include "Advent2019/advent2019.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(day03Tests)
	{
	public:
		
		TEST_METHOD(testData)
		{
			auto day03_testdata = ReadAllText(PROJECT_DIR "input\\day03testdata.txt");
			day03(day03_testdata);

			Assert::AreEqual(1, 1);
		}

		TEST_METHOD(test_absolute)
		{
			Assert::AreEqual(10, absolute(-10));
			Assert::AreEqual(10, absolute(10));
			Assert::AreEqual(0, absolute(0));
		}

		TEST_METHOD(test_inRange)
		{
			Assert::AreEqual(true, inRange(0, 100, 50));
			Assert::AreEqual(true, inRange(-100, 100, 50));
			Assert::AreEqual(true, inRange(-100, 100, -50));
			Assert::AreEqual(true, inRange(-100, 0, -50));

			Assert::AreEqual(false, inRange(0, 100, 101));
			Assert::AreEqual(false, inRange(0, 100, -1));
			Assert::AreEqual(false, inRange(-100, 0, 1));
			Assert::AreEqual(false, inRange(-100, 0, -101));
			
		}
	};
}
