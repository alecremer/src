# cmake_minimum_required(VERSION 2.8.3)

# project(laracna)

# find_package(catkin REQUIRED)

# catkin_package()

# find_package(roslaunch)

# foreach(dir config launch meshes urdf)
# 	install(DIRECTORY ${dir}/
# 		DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/${dir})
# endforeach(dir)

cmake_minimum_required(VERSION 3.5)

project(laracna)

# Encontre pacotes do ROS2
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

# Defina o pacote para instalação
install(DIRECTORY config launch meshes urdf
  DESTINATION share/${PROJECT_NAME}
)

# Adicionar executáveis ou bibliotecas (se necessário)
# add_executable(example_node src/example_node.cpp)
# ament_target_dependencies(example_node rclcpp)

# Instalar executáveis ou bibliotecas (se necessário)
# install(TARGETS example_node DESTINATION lib/${PROJECT_NAME})

ament_package()
