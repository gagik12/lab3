// TrimBlanksTests.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "../Car/Car.h"
#include <boost/function.hpp>

struct CCarFixture
{
	CCar vaz;
};

void ExpectSuccess(CCar vaz, boost::function<bool(CCar & vaz)> const& operation)
{
	BOOST_CHECK(operation);
}


BOOST_FIXTURE_TEST_SUITE(Car, CCarFixture)
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
   BOOST_AUTO_TEST_CASE(on_create_speed_is_0)
   {
	   BOOST_CHECK(vaz.GetSpeed() == 0);
   }
   BOOST_AUTO_TEST_CASE(gear_0_by_default)
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
		}
        BOOST_AUTO_TEST_CASE(on_engine_on_speed_is_0)
		{
			BOOST_CHECK_EQUAL(vaz.GetSpeed(), 0);
		}
		BOOST_AUTO_TEST_CASE(cant_set_a_reverse_gear)
		{
			BOOST_CHECK(vaz.SetGear(-1) && (vaz.GetGear() == -1));
		}


		struct when_reverse_gear_set_ : when_turned_on_
		{
			when_reverse_gear_set_()
			{
				vaz.SetGear(-1);
				vaz.SetSpeed(15);
			}
		};

		BOOST_FIXTURE_TEST_SUITE(when_reverse_gear_set, when_reverse_gear_set_)
			BOOST_AUTO_TEST_CASE(can_set_speed_ranged_from_0_to_20)
			{
				vaz.SetSpeed(20);
				BOOST_CHECK_EQUAL(vaz.GetSpeed(), -20);
			}
			BOOST_AUTO_TEST_CASE(can_set_the_neutral_gear)
			{
				BOOST_CHECK(vaz.SetGear(0));
				BOOST_CHECK_EQUAL(vaz.GetGear(), 0);
			}

		    BOOST_AUTO_TEST_CASE(can_not_set_the_first_gear)
			{
				BOOST_CHECK(!vaz.SetGear(1));
				BOOST_CHECK_EQUAL(vaz.GetGear(), -1);
			}

			BOOST_AUTO_TEST_CASE(can_not_switch_to_the_first_speed_is_when_gear_equal_to_reverse)
			{
				BOOST_CHECK(!vaz.SetGear(1));
				BOOST_CHECK_EQUAL(vaz.GetGear(), -1);
			}

			BOOST_AUTO_TEST_CASE(can_switch_to_the_first_speed_is_when_gear_equal_to_neutral)
			{
				BOOST_CHECK(vaz.SetGear(0));
				BOOST_CHECK(vaz.SetSpeed(0));
				BOOST_CHECK(vaz.SetGear(1));
				BOOST_CHECK_EQUAL(vaz.GetGear(), 1);
			}

			struct when_neutral_gear_set_ : when_turned_on_
			{
				when_neutral_gear_set_()
				{
					vaz.SetGear(1);
					vaz.SetSpeed(10);
					vaz.SetGear(0);
				}
			};
			BOOST_FIXTURE_TEST_SUITE(when_neutral_gear_set, when_neutral_gear_set_)
			    BOOST_AUTO_TEST_CASE(car_can_not_gain_speed)
			    {
			    	BOOST_CHECK(!vaz.SetSpeed(20));
			    	BOOST_CHECK_EQUAL(vaz.GetSpeed(), 10);
			    }
				BOOST_AUTO_TEST_CASE(car_can_reduce_speed)
			    {
			    	BOOST_CHECK(vaz.SetSpeed(5));
			    	BOOST_CHECK_EQUAL(vaz.GetSpeed(), 5);
			    }
			BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
