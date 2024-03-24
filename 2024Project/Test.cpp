#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include "Game.h"
#include "Rivers.h"


struct RiversFixture {
    Rivers riverFiles{ {"Europe.txt","Asia.txt","Africa.txt","South America.txt"} };
};

BOOST_FIXTURE_TEST_SUITE(RiversTests, RiversFixture)

//BOOST_AUTO_TEST_CASE(testSetMode) {
//    
//    BOOST_REQUIRE_EQUAL(riverFiles.setMode(1), riverFiles.myMode);
//}

BOOST_AUTO_TEST_CASE(testSameContinent) {

    //Test if two african rivers are the same continent - should return true
    BOOST_CHECK(riverFiles.sameContinent("Zambezi", "Chari"));
    //Test if two african rivers are the same continent but one is lowercase - should return false
    BOOST_CHECK(!riverFiles.sameContinent("zambezi", "Chari"));
    //Test if one river is not in my files - should return false
    BOOST_CHECK(!riverFiles.sameContinent("", "Chaget jri"));
    //Test if one river is from africa, and one is from europe - should return false
    BOOST_CHECK(!riverFiles.sameContinent("Zambezi", "Danube"));
}

BOOST_AUTO_TEST_CASE(testGetCont) {
    //Test is entering river "Nile" gets correct continent Africa - should pass
    BOOST_CHECK_EQUAL(riverFiles.getContinent("Nile"), "Africa");
    //Test is entering river "Rhine" gets correct continent Europe - should pass
    BOOST_CHECK_EQUAL(riverFiles.getContinent("Rhine"), "Europe");
    //Test is entering river "Dee" should return "" as it doesn't exist in files - should pass
    BOOST_CHECK_EQUAL(riverFiles.getContinent("Dee"), "");

}
BOOST_AUTO_TEST_SUITE_END()


//////////////////////////////////////////Game Tests//////////////////////////////////////////

BOOST_FIXTURE_TEST_SUITE(GameTests, RiversFixture)


//BOOST_AUTO_TEST_CASE(testGetRivers) {
//    std::string r1 = riverFiles.getRandomRiver();
//    std::string r2 = riverFiles.getRandomRiver();
//    std::string test = r1 + "\n" + r2 + "\n";
//    BOOST_CHECK(test, Game::getRivers());
//}



//void Game::userTime(std::ostream& out, std::istream& in) {
//    auto start = std::chrono::high_resolution_clock::now();
//    in >> stringInput;
//    ;
//    dur = duration.count();
//}


//BOOST_AUTO_TEST_CASE(testUserTime) {
//    auto start = std::chrono::high_resolution_clock::now();
//    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
//    std::string str = "hello";
//    auto end = std::chrono::high_resolution_clock::now();
//    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
//    double testDur = duration.count();
//    BOOST_CHECK(Game::userTime(testDur), Game::dur);
//}

BOOST_AUTO_TEST_SUITE_END()
