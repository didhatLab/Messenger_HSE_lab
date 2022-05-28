cmake_minimum_required(VERSION 3.22)
project(TestClient C)

set(CMAKE_C_STANDARD 99)

add_executable(TestClient main.c structures/User/user.c structures/User/user.h structures/Connection/connection_data.c structures/Connection/connection_data.h RequestHandler/Main/RequestHandler.c RequestHandler/Main/RequestHandler.h InputForms/forms.c InputForms/forms.h RequestHandler/HelpScripts/RequestMaker.c RequestHandler/HelpScripts/RequestMaker.h DataBaseController/dbController.c DataBaseController/dbController.h UserInterface/Commands.c UserInterface/Commands.h structures/Friends/Freinds.cpp structures/Friends/Freinds.h GlobalConfigs/configs.c GlobalConfigs/configs.h structures/Message/message.c structures/Message/message.h StartConfiguration/starApp.c StartConfiguration/starApp.h main.c DataBaseController/dbController.c GlobalConfigs/configs.c RequestHandler/HelpScripts/RequestMaker.c RequestHandler/Main/RequestHandler.c structures/Message/message.h DataBaseConfiguration/dbConfiguration.c DataBaseConfiguration/dbConfiguration.h)

find_package(SQLite3 REQUIRED)
target_link_libraries(${PROJECT_NAME} SQLite::SQLite3)
