// TrimBlanksTests.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "../Car/Car.h"

struct CCarFixture
{
	CCar vaz;
};

BOOST_FIXTURE_TEST_SUITE(SetGear_funv, CCarFixture)
   BOOST_AUTO_TEST_CASE(is_turned_off_by_default)
   {
		BOOST_CHECK(!vaz.IsTurnOnEngine());
   }

   BOOST_AUTO_TEST_CASE(cant_set_gear_when_turned_off)
   {
	   BOOST_CHECK(!vaz.SetGear(6));
	   BOOST_CHECK_EQUAL(vaz.GetGear(), 0);
   }

   BOOST_AUTO_TEST_CASE(can_be_turned_on)
   {
	   vaz.TurnOnEngine();
	   BOOST_CHECK(vaz.IsTurnOnEngine());
   }

   BOOST_AUTO_TEST_CASE(displays_channel_0_by_default)
   {
	   BOOST_CHECK_EQUAL(vaz.GetGear(), 0);
   }

   struct when_turned_on_ : CCarFixture
   {
	   when_turned_on_()
	   {
		   vaz.TurnOnEngine();
	   }
   };

   BOOST_FIXTURE_TEST_SUITE(when_turned_on, when_turned_on_)
		BOOST_AUTO_TEST_CASE(can_be_turned_off)
		{
			BOOST_CHECK(vaz.TurnOffEngine());
			BOOST_CHECK(!vaz.TurnOffEngine()); 
		}
       // позволяет выбрать передачу от -1 до 5
		BOOST_AUTO_TEST_CASE(can_select_gear_from_minus_1_to_5)
		{
			BOOST_CHECK(!vaz.SetGear(6));
			BOOST_CHECK_EQUAL(vaz.GetGear(), 0);

			BOOST_CHECK(!vaz.SetGear(-2));
			BOOST_CHECK_EQUAL(vaz.GetGear(), 0);

			BOOST_CHECK(vaz.SetGear(-1));
			BOOST_CHECK_EQUAL(vaz.GetGear(), -1);

			BOOST_CHECK(!vaz.SetGear(4));
			BOOST_CHECK_EQUAL(vaz.GetGear(), -1);
		}	

		BOOST_AUTO_TEST_CASE(can_select_the_speed_depending_on_the_gear)
		{
			BOOST_CHECK(!vaz.SetGear(3));
			BOOST_CHECK(!vaz.SetSpeed(30));
			BOOST_CHECK_EQUAL(vaz.GetSpeed(), 0);

			BOOST_CHECK(vaz.SetGear(1));
			BOOST_CHECK(vaz.SetSpeed(20));
			BOOST_CHECK_EQUAL(vaz.GetSpeed(), 20);

			BOOST_CHECK(vaz.SetGear(0));
			BOOST_CHECK_EQUAL(vaz.GetSpeed(), 20); //скорость та же

			BOOST_CHECK(!vaz.SetSpeed(24)); //пытаемся увеличить скорость 
			BOOST_CHECK_EQUAL(vaz.GetSpeed(), 20);

			BOOST_CHECK(vaz.SetSpeed(17)); //уменьшили скорость
			BOOST_CHECK_EQUAL(vaz.GetSpeed(), 17);

			BOOST_CHECK(!vaz.SetGear(-1)); //пытаемся поставить заднюю передачу при движении вперед
			BOOST_CHECK_EQUAL(vaz.GetGear(), 0);

			BOOST_CHECK(vaz.SetSpeed(0)); //остановились и переключили на заднюю
			BOOST_CHECK(vaz.SetGear(-1));
			BOOST_CHECK_EQUAL(vaz.GetGear(), -1);

			BOOST_CHECK(vaz.SetSpeed(19)); //двигаемся назад 
			BOOST_CHECK_EQUAL(vaz.GetSpeed(), 19);

			BOOST_CHECK(vaz.SetGear(0));//переключить на нейтралку
			BOOST_CHECK_EQUAL(vaz.GetGear(), 0);
			BOOST_CHECK_EQUAL(vaz.GetSpeed(), 19);			
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()