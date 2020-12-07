#include "pch.h"
#include "CppUnitTest.h"
#include "..\cpp\Osoba.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testy
{
	TEST_CLASS(Testy_Osoba)
	{
	public:
		
		TEST_METHOD(TestOsobaKonstruktor)
		{
			Osoba *o = new Osoba("Jan","Pucha");
			string imie = "Jan";
			string result= o->getImie();
			Assert::AreEqual(imie,result);
		}
		TEST_METHOD(TestOsobaSetWiek)
		{
			Osoba* o = new Osoba("Jan", "Pucha");
			int wiek = 57;
			o->setWiek(wiek);
			int result = o->getWiek();
			Assert::AreEqual(wiek, result);
		}
		TEST_METHOD(TestOsobaSetImie)
		{
			Osoba* o = new Osoba("Jan", "Pucha");
			string imie = "Andrzej";
			o->setImie(imie);
			string result = o->getImie();
			Assert::AreEqual(imie, result);
		}
		TEST_METHOD(TestOsobaSetNazwisko)
		{
			Osoba* o = new Osoba("Jan", "Pucha");
			string n = "Zegarmistrz";
			o->setNazwisko(n);
			string result = o->getNazwisko();
			Assert::AreEqual(n, result);
		}
	};
}
