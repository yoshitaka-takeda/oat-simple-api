# oat++-simple-api

Current program directory listings:
```text
oat-simple-api
├── CMakeLists.txt
├── .env.example
├── .gitignore
├── README.md
├── src
│   ├── AppComponent.hpp
│   ├── App.cpp
│   ├── controller
│   │   └── AppController.hpp
│   ├── DotEnv.hpp
│   └── dto
│       └── MessageDto.hpp
├── test
│   ├── app
│   │   ├── AppApiTestClient.hpp
│   │   └── TestComponent.hpp
│   ├── AppControllerTest.cpp
│   ├── AppControllerTest.hpp
│   └── tests.cpp
└── test-result
    ├── api-running-on-port-8000.png
    ├── api-test-result.png
    └── server-running-indicator.png
```

Server Running Indicator:
![Server Running with dotenv applied](test-result/server-running-indicator.png)

Json result within browser (on http):
![Json Result](test-result/api-running-on-port-8000.png)

Api Call test result:
![simple-api-test](test-result/api-test-result.png)