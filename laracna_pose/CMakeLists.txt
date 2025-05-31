cmake_minimum_required(VERSION 3.8)
project(laracna_pose)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find  rosdependencies
find_package(ament_cmake REQUIRED)

find_package(std_msgs REQUIRED)
find_package(rclcpp REQUIRED)

# external dependencies
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.5.4 # ou a versão mais recente
)
FetchContent_MakeAvailable(Catch2)

enable_testing()

include_directories(include)


# add_subdirectory(tests)



add_executable(pose_node 
  src/publisher_creator.cpp
  src/leg_publisher.cpp
  src/main.cpp
)


ament_target_dependencies(pose_node rclcpp std_msgs)

# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

# Install launch files
install(
  DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)
install(TARGETS pose_node
  DESTINATION lib/${PROJECT_NAME}
)

# Install nodes
# install(
#   TARGETS [node-names]
#   DESTINATION lib/${PROJECT_NAME}
# )

ament_package()
