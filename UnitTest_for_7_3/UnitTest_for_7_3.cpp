#include "pch.h"
#include "CppUnitTest.h"
#include <ObjIdlbase.h>
#include "../Laboratorna 7_3rec/Lab 7_3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestfor73
{
	TEST_CLASS(UnitTestfor73)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			bool result = false;
			int count = 0;
			int mas[3][3] =
			{
				{-1, 0, -6},
				{4, 0, -2},
				{-7, -8, 0}
			};
			int* pa[3] = { mas[0], mas[1], mas[2] };
			Part1_CountCols(pa, 3, 3, count, result, 0);
			int a = count;
			Assert::AreEqual(a, 5);
		}
	};
}
