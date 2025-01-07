cmake_minimum_required(VERSION 3.10)
project(stack)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Set the CMAKE_PREFIX_PATH to include the MySQL Connector/C++ installation directory
set(CMAKE_PREFIX_PATH "/usr/local/Cellar/mysql-connector-c++/9.1.0")

# Tell CMake where to find the MySQL Connector/C++ header files (X DevAPI)
include_directories(/usr/local/Cellar/mysql-connector-c++/9.1.0/include)

# Set the CMAKE_MODULE_PATH to the directory containing the package configuration file
set(CMAKE_MODULE_PATH "/usr/local/Cellar/mysql-connector-c++/9.1.0")

# Find the MySQL Connector/C++ library (X DevAPI)
find_package(mysql-concpp REQUIRED CONFIG)

# Add executable, specifying the source files
add_executable(stack
    core/Controller.cpp
    core/Model.cpp
    core/View.cpp
    src/main.cpp
)

# Link against the MySQL Connector/C++ library (X DevAPI)
target_link_libraries(stack PRIVATE /usr/local/Cellar/mysql-connector-c++/9.1.0/lib/libmysqlcppconnx.dylib)

# Add custom command to run Flyway migrations
add_custom_target(run_migrations
    COMMAND flyway -configFiles=flyway.conf migrate
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running Flyway migrations"
)

# Add a custom command to rebuild the project if necessary
add_custom_target(rebuild
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target stack
    COMMENT "Rebuilding the stack project"
)

# Add dependencies for the rebuild command to ensure migrations are run first
add_dependencies(rebuild run_migrations)
set_target_properties(stack PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
