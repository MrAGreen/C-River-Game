#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include "Game.h"
#include "Rivers.h"


struct RiversFixture {
    Rivers riverFiles{ {"Europe.txt","Asia.txt","Africa.txt","South America.txt"} };
};

BOOST_FIXTURE_TEST_SUITE(RiversTests, RiversFixture)

BOOST_AUTO_TEST_CASE(testSetMode) {
    int test = 1;
    BOOST_CHECK_EQUAL(riverFiles.setMode(test), riverFiles.myMode;);
}

BOOST_AUTO_TEST_CASE(testSameContinent) {

    BOOST_CHECK(riverFiles.sameContinent("Zambezi", "Chari"));
    BOOST_CHECK(!riverFiles.sameContinent("Zambezi", "Danube"));
}

BOOST_AUTO_TEST_CASE(testGetCont) {
    BOOST_CHECK_EQUAL(riverFiles.getContinent("Nile"), "Africa");
    BOOST_CHECK_EQUAL(riverFiles.getContinent("Rhine"), "Europe");
    BOOST_CHECK_EQUAL(riverFiles.getContinent("Dee"), "");

}

BOOST_AUTO_TEST_SUITE_END()
