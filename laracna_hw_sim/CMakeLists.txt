cmake_minimum_required(VERSION 3.8)
project(laracna_hw_sim)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rclcpp REQUIRED)

include_directories(include)

# Adicione as bibliotecas
add_library(driver_sim src/driver_sim.cpp)
ament_target_dependencies(driver_sim rclcpp std_msgs)

add_library(ik src/ik.cpp)
ament_target_dependencies(ik rclcpp std_msgs)

add_library(leg_move_controller src/leg_move_controller.cpp)
ament_target_dependencies(leg_move_controller rclcpp std_msgs)

add_library(move_manager src/move_manager.cpp )
ament_target_dependencies(move_manager rclcpp std_msgs)

add_executable(laracna_hw_sim_node src/laracna_hw_sim.cpp)
target_link_libraries(laracna_hw_sim_node driver_sim ik leg_move_controller move_manager)

ament_target_dependencies(laracna_hw_sim_node rclcpp)

target_link_libraries(leg_move_controller driver_sim ik)
target_link_libraries(driver_sim leg_move_controller)
target_link_libraries(move_manager leg_move_controller)

install(TARGETS
  laracna_hw_sim_node
  DESTINATION lib/${PROJECT_NAME}
)

install(TARGETS
  driver_sim
  ik
  leg_move_controller
  move_manager
  DESTINATION lib/${PROJECT_NAME}
)


install(DIRECTORY launch/
  DESTINATION share/${PROJECT_NAME}/launch)


install(DIRECTORY config/
  DESTINATION share/${PROJECT_NAME}/config)

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

ament_package()
