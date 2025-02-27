#define BOOST_TEST_MAIN
#include "Game.h"
#include "Rivers.h"
#include <boost/test/included/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
namespace bdata = boost::unit_test::data;

bool SortDurationCopy(std::pair<double, std::string> x, std::pair<double, std::string> y)
{
    return x.first < y.first;

}

struct RiversFixture {

    Rivers riverFiles{ {"Europe.txt","Asia.txt","Africa.txt","South America.txt"} };
    std::mt19937_64 randomGen;
    std::vector<double> weights;

    std::vector<std::string> files{ "Europe.txt","Asia.txt","Africa.txt","South America.txt" };
    void setWeight() {
        for (auto& i : files)
        {
            weights.push_back(1);
        }
    }
};

BOOST_FIXTURE_TEST_SUITE(RiversTests, RiversFixture);

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

BOOST_AUTO_TEST_CASE(testGetMode) {

    riverFiles.setMode(1);
    int num = riverFiles.getMode();
    BOOST_CHECK(num, 1);
}

BOOST_AUTO_TEST_CASE(testGetScore) {
    Rivers r(riverFiles);
    Game myGame(r);

    myGame.incrementScore();
    int num = myGame.getScore();
    BOOST_CHECK_EQUAL(num, 1);
}

BOOST_AUTO_TEST_CASE(testGetTotal) {
    Rivers r(riverFiles);
    Game myGame(r);

    myGame.incrementTotal();
    int num = myGame.getTotal();
    BOOST_CHECK_EQUAL(num, 1);
}

BOOST_AUTO_TEST_CASE(testReset) {
    Rivers r(riverFiles);
    Game myGame(r);
    //set previous working tests to add 1 to each.
    myGame.incrementScore();
    myGame.incrementTotal();

    myGame.reset();
    //if reset worked variables should be 0 now and add up to 0 instead of 2.
    int num1 = myGame.getTotal();
    int num2 = myGame.getScore();
    
    int result = num1 + num2;

    BOOST_CHECK_EQUAL(result, 0);
}

BOOST_AUTO_TEST_CASE(testGetFastest) {
    Rivers r(riverFiles);
    Game myGame(r);

    double dur = 20;
    std::string river1 = "Hello";
    std::string river2 = "There";
    std::pair<double, std::string> test = std::make_pair(dur, river1 + ", " + river2 + ", " + std::to_string(dur));
    std::string testString = (river1 + ", " + river2 + ", " + std::to_string(dur));
    std::vector<std::string> testVec;
    std::vector<std::string> getFastestResults;

    testVec.push_back(testString);
    myGame.fastestTimes.push_back(test);
    getFastestResults = myGame.getFastest();
    BOOST_CHECK(getFastestResults == testVec);
}

BOOST_AUTO_TEST_CASE(testSortFunction) {
    std::string test;
    std::pair<double, std::string> testPair1 = std::make_pair(11, "There");
    std::pair<double, std::string> testPair2 = std::make_pair(10, "Hello");
    //mock example of function that's unable to be passed from game.h. pair1 is greater than pair2 so it should return false;
    //used to organise my getfastest();
    BOOST_CHECK(!SortDurationCopy(testPair1, testPair2));
}

BOOST_AUTO_TEST_CASE(testFileRead) {
    std::mutex mutex;
    std::vector<std::string> testFiles;
    for (auto& f : testFiles) {
        riverFiles.fileRead(f, mutex);
        BOOST_CHECK(!f.empty());
    }
}

//Parameterised Test//

BOOST_DATA_TEST_CASE(getCont, bdata::make({ "Nile", "nile", "Rhine", "Dee", "Zambezi", "Indus", "", "Amazon" }), array) {

    std::map<std::string, std::string> rivers = {
     {"Nile", "Africa"},
     {"nile", ""},
     {"Rhine", "Europe"},
     {"Dee", ""},
     {"Zambezi", "Africa"},
     {"Indus", "Asia"},
     {"", ""},
     {"Amazon", "South America"},
    };

    BOOST_CHECK_EQUAL(riverFiles.getContinent(array), rivers[array]);
}

//Random Test//

BOOST_AUTO_TEST_CASE(randomRiver) {

    std::vector<std::string> testVec;

    for (int i = 0; i < 94; ++i) {
        std::string riv = riverFiles.getRandomRiver();
        BOOST_CHECK(!riv.empty());
        BOOST_CHECK(riv != "");
        testVec.push_back(riv);

    };
    //should get 94 rivers from the 4 files we've been given

    BOOST_CHECK(testVec.size() == 94);

}

BOOST_AUTO_TEST_SUITE_END()
