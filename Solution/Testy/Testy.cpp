#include "pch.h"
#include "CppUnitTest.h"
#include "..\headers\Osoba.h"
#include "..\headers\Ui.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testy
{
	TEST_CLASS(Testy)
	{
	public:
		TEST_METHOD(TestOsobaSetGetImie) {
			/*
			Osoba* o = new Osoba("Janusz", "Hasio",1,2,3);
			string imie = "Janusz";
			string naz = "Hasio";
			string result = o->getImie();
			Assert::AreEqual(imie, result);
			*/
		}
		
	};
	TEST_CLASS(UiTests)
	{
	public:
		TEST_METHOD(TestSignInUp) {
			//test metody SignInUpMenu
			/*
			Ui ui = Ui();
			int n = ui.signInUpMenu();

			Assert::AreEqual(1, n);
			*/
		}
	};
}
