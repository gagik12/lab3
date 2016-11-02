// TrimBlanksTests.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "../Car/Car.h"
#include <boost/function.hpp>

struct CCarFixture
{
    CCar vaz;
};

void ExpectFailure(CCar vaz, const std::function<bool(CCar & car)> & operation)
{
    CCar clone(vaz);
    BOOST_CHECK(!operation(clone));
    BOOST_CHECK_EQUAL(clone.IsTurnOnEngine(), vaz.IsTurnOnEngine());
    BOOST_CHECK(clone.GetGear() == vaz.GetGear());
    BOOST_CHECK_EQUAL(clone.GetCurrentSpeed(), vaz.GetCurrentSpeed());
}

BOOST_FIXTURE_TEST_SUITE(Car, CCarFixture)
   BOOST_AUTO_TEST_CASE(is_turned_off_by_default)
   {
        BOOST_CHECK(!vaz.IsTurnOnEngine());
   }

   BOOST_AUTO_TEST_CASE(cant_set_gear_when_turned_off)
   {
        ExpectFailure(vaz, [](auto & vaz)
        {
            return vaz.SetGear(6);
        });
        BOOST_CHECK_EQUAL(vaz.GetGear(), 0);
   }

   BOOST_AUTO_TEST_CASE(can_be_turned_on)
   {
        vaz.TurnOnEngine();
        BOOST_CHECK(vaz.IsTurnOnEngine());
   }
   BOOST_AUTO_TEST_CASE(on_create_speed_is_0)
   {
       BOOST_CHECK(vaz.GetCurrentSpeed() == 0);
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
        BOOST_AUTO_TEST_CASE(on_speed_is_0)
        {
            BOOST_CHECK_EQUAL(vaz.GetCurrentSpeed(), 0);
        }
        BOOST_AUTO_TEST_CASE(can_set_a_reverse_gear)
        {
            BOOST_CHECK(vaz.SetGear(-1) && (vaz.GetGear() == -1));
        }
        BOOST_AUTO_TEST_CASE(when_the_speed_is_not_zero_the_engine_doest_off) 
        {
            BOOST_CHECK(vaz.SetGear(1));
            BOOST_CHECK(vaz.SetSpeed(20));
            ExpectFailure(vaz, [](auto & vaz)
            {
                return vaz.TurnOffEngine();
            });
        }

        BOOST_AUTO_TEST_CASE(engine_can_only_be_off_in_the_neutral_position_at_zero_speed)
        {
            BOOST_CHECK(vaz.TurnOffEngine());
        }

        BOOST_AUTO_TEST_CASE(it_is_impossible_to_accelerate_in_neutral)
        {
            BOOST_CHECK(vaz.GetGear() == 0);
            ExpectFailure(vaz, [](auto & vaz)
            {
                return vaz.SetSpeed(10);
            });
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
                BOOST_CHECK_EQUAL(vaz.GetCurrentSpeed(), 20);
            }
            BOOST_AUTO_TEST_CASE(can_set_the_neutral_gear)
            {
                BOOST_CHECK(vaz.SetGear(0));
                BOOST_CHECK_EQUAL(vaz.GetGear(), 0);
            }

            BOOST_AUTO_TEST_CASE(can_not_set_the_first_gear)
            {
                ExpectFailure(vaz, [](auto & vaz)
                {
                    return vaz.SetGear(1);
                });
                BOOST_CHECK_EQUAL(vaz.GetGear(), -1);
            }

            BOOST_AUTO_TEST_CASE(can_not_switch_to_the_first_speed_is_when_gear_equal_to_reverse)
            {
                ExpectFailure(vaz, [](auto & vaz)
                {
                    return vaz.SetGear(1);
                });
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
                BOOST_AUTO_TEST_CASE(car_can_not_accelerated_speed) //невозможно ускоритсься на нейтральном передаче
                {
                    ExpectFailure(vaz, [](auto & vaz)
                    {
                        return vaz.SetSpeed(20);
                    });
                    BOOST_CHECK_EQUAL(vaz.GetCurrentSpeed(), 10);
                }
                BOOST_AUTO_TEST_CASE(car_can_reduce_speed)
                {
                    BOOST_CHECK(vaz.SetSpeed(5));
                    BOOST_CHECK_EQUAL(vaz.GetCurrentSpeed(), 5);
                }

                BOOST_AUTO_TEST_CASE(car_cant_increase_speed)
                {
                    BOOST_CHECK(vaz.SetSpeed(5));
                    BOOST_CHECK_EQUAL(vaz.GetCurrentSpeed(), 5);
                }

                BOOST_AUTO_TEST_CASE(while_moving_forward_can_not_be_turned_reverse_gear) // при движении вперед нельзя включить заднюю передачу
                {
                    ExpectFailure(vaz, [](auto & vaz)
                    {
                        return vaz.SetGear(-1);
                    });
                }
            BOOST_AUTO_TEST_SUITE_END()

            struct when_the_car_is_moving_ : when_turned_on_
            {
                when_the_car_is_moving_()
                {
                    vaz.SetGear(1);
                    vaz.SetSpeed(10);
                }
            };
            BOOST_FIXTURE_TEST_SUITE(when_the_car_is_moving, when_the_car_is_moving_)
                BOOST_AUTO_TEST_CASE(car_cant_drive_at_a_speed_which_ist_suitable_for_the_current_gear) //автомобиль не может ехать со скоростью, не подходящей для текущей передачи
                {
                    ExpectFailure(vaz, [](auto & vaz)
                    {
                        return vaz.SetSpeed(40);
                    });
                }

                BOOST_AUTO_TEST_CASE(car_cant_change_the_gear_ist_available_during_motion_at_the_current_speed)//сменить передачу, недоступную при движении на текущей скорости.
                {
                    ExpectFailure(vaz, [](auto & vaz)
                    {
                        return vaz.SetGear(2);
                    });
                }

                BOOST_AUTO_TEST_CASE(while_moving_forward_can_not_be_turned_reverse_gear) // при движении вперед нельзя включить заднюю передачу
                {
                    ExpectFailure(vaz, [](auto & vaz)
                    {
                        return vaz.SetGear(-1);
                    });
                }
            BOOST_AUTO_TEST_SUITE_END()
        BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()