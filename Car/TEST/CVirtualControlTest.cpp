#include "stdafx.h"
#include "../Car/VirtualControl.h"
#include <boost/function.hpp>

struct CVirtualControlFixture
{
    CVirtualControlFixture();
    CCar vaz;
    std::shared_ptr<CVirtualControl> virtualControl;
};

CVirtualControlFixture::CVirtualControlFixture()
{
    virtualControl = std::make_shared<CVirtualControl>(vaz, std::cin, std::cout);
}


BOOST_FIXTURE_TEST_SUITE(VirtualControl, CVirtualControlFixture)
   BOOST_AUTO_TEST_CASE(engine_can_be_turned_on)
   {
        std::istringstream command("EngineOn");
        BOOST_CHECK(virtualControl->TurnOnEngine(command));
        BOOST_CHECK(!virtualControl->TurnOnEngine(command));
   }
   struct when_turned_on_ : CVirtualControlFixture
   {
       when_turned_on_()
       {
           std::istringstream command("EngineOn");
           virtualControl->TurnOnEngine(command);
       }
   };
   BOOST_FIXTURE_TEST_SUITE(when_turned_on, when_turned_on_)
       BOOST_AUTO_TEST_CASE(cant_set_a_reverse_gear)
       {
       std::istringstream gear("-1");
       BOOST_CHECK(virtualControl->SetGear(gear));
       BOOST_CHECK_EQUAL(vaz.GetGear(), -1);
       }

       struct when_reverse_gear_set_ : when_turned_on_
       {
           when_reverse_gear_set_()
           {
               std::istringstream gear("-1");
               virtualControl->SetGear(gear);
           }
       };
       BOOST_FIXTURE_TEST_SUITE(when_reverse_gear_set, when_reverse_gear_set_)
           BOOST_AUTO_TEST_CASE(can_set_speed_ranged_from_0_to_20)
           {
               std::istringstream speed("20");
               BOOST_CHECK(virtualControl->SetSpeed(speed));
               BOOST_CHECK_EQUAL(vaz.GetCurrentSpeed(), 20);
           }
       BOOST_AUTO_TEST_SUITE_END()
   BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()