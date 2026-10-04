#ifndef AppControllerTest_hpp
#define AppControllerTest_hpp

#include "oatpp-test/UnitTest.hpp"

class AppControllerTest : public oatpp::test::UnitTest {
public:

  AppControllerTest() : UnitTest("TEST[AppControllerTest]"){}
  void onRun() override;

};

#endif // AppControllerTest_hpp