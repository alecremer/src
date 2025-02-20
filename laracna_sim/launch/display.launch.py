import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node


import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

def generate_launch_description():
    package_name = "laracna_sim"
    package_path = get_package_share_directory('laracna_sim')
    urdf_file = os.path.join(package_path, 'urdf', 'laracna.urdf')
    csv_file = os.path.join(package_path, 'data', 'laracna.csv')
    pkg_share = get_package_share_directory(package_name)


    # Argumentos de lançamento
    use_sim_time = LaunchConfiguration("use_sim_time", default="true")
    
    # Gazebo
    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(get_package_share_directory("gazebo_ros"), "launch", "gazebo.launch.py")
        ),
        launch_arguments={"use_sim_time": use_sim_time}.items(),
    )

    # RViz
    rviz_config_file = os.path.join(pkg_share, "config", "display.rviz")
    rviz_node = Node(
        package="rviz2",
        executable="rviz2",
        arguments=["-d", rviz_config_file],
        output="screen"
    )

    # Spawn do robô no Gazebo
    spawn_robot = Node(
        package="gazebo_ros",
        executable="spawn_entity.py",
        arguments=["-entity", "robot", "-file", urdf_file, "-x", "0", "-y", "0", "-z", "1"],
        output="screen"
    )

    return LaunchDescription([
        DeclareLaunchArgument("use_sim_time", default_value="true", description="Use simulation time"),
        gazebo,
        spawn_robot,
        rviz_node,
    ])

    # return LaunchDescription([
    #     Node(
    #         package='robot_state_publisher',
    #         executable='robot_state_publisher',
    #         parameters=[{'robot_description': open(urdf_file).read()}],
    #         output='screen'
    #     ),
    #     Node(
    #         package='rviz2',
    #         executable='rviz2',
    #         output='screen'
    #     )
    # ])

# import os

# from ament_index_python.packages import get_package_share_directory
# from launch import LaunchDescription
# from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
# from launch.launch_description_sources import PythonLaunchDescriptionSource
# from launch.substitutions import LaunchConfiguration
# from launch_ros.actions import Node

# def generate_launch_description():
#     package_name = "laracna_sim"

#     # Caminhos dos arquivos
#     pkg_share = get_package_share_directory(package_name)
#     urdf_file = os.path.join(pkg_share, "urdf", "laracna.urdf")
#     world_file = os.path.join(pkg_share, "worlds", "empty.world")  # Ajuste conforme necessário

#     # Argumentos de lançamento
#     use_sim_time = LaunchConfiguration("use_sim_time", default="true")

#     # Gazebo
#     gazebo = IncludeLaunchDescription(
#         PythonLaunchDescriptionSource(
#             os.path.join(get_package_share_directory("gazebo_ros"), "launch", "gazebo.launch.py")
#         ),
#         launch_arguments={"use_sim_time": use_sim_time}.items(),
#     )

#     # RViz
#     rviz_config_file = os.path.join(pkg_share, "config", "display.rviz")
#     rviz_node = Node(
#         package="rviz2",
#         executable="rviz2",
#         arguments=["-d", rviz_config_file],
#         output="screen"
#     )

#     # Spawn do robô no Gazebo
#     spawn_robot = Node(
#         package="gazebo_ros",
#         executable="spawn_entity.py",
#         arguments=["-entity", "robot", "-file", urdf_file, "-x", "0", "-y", "0", "-z", "1"],
#         output="screen"
#     )

#     return LaunchDescription([
#         DeclareLaunchArgument("use_sim_time", default_value="true", description="Use simulation time"),
#         gazebo,
#         spawn_robot,
#         rviz_node,
#     ])
