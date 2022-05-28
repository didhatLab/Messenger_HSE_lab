cmake_minimum_required(VERSION 3.22)
project(TestServer C)

set(CMAKE_C_STANDARD 99)

add_executable(TestServer main.c dbController/dbController.c dbController/dbController.h Structures/MessageList/MessageList.c Structures/MessageList/MessageList.h RequestHandler/RequestHandler.c RequestHandler/RequestHandler.h Structures/RequestAnswer/RequestAnswer.c Structures/RequestAnswer/RequestAnswer.h GlobalConfigs/GlobalCOnfigs.c GlobalConfigs/GlobalCOnfigs.h HelpScripts/HelpScripts.c HelpScripts/HelpScripts.h StartConfiguration/StartConfiguration.c StartConfiguration/StartConfiguration.h)

find_package(SQLite3 REQUIRED)
target_link_libraries(${PROJECT_NAME} SQLite::SQLite3)
