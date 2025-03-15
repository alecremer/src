from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='example',
            namespace='example_sub',
            executable='subscriber_node',
            output='screen',
            name='subscriber_node'
        ),
        Node(
            package='example',
            namespace='example_pub',
            executable='publisher_node',
            output='screen',
            name='publisher_node'
        ),
        # u can use remapping here
        # Node(
        #     package='turtlesim',
        #     executable='mimic',
        #     name='mimic',
        #     remappings=[
        #         ('/input/pose', '/turtlesim1/turtle1/pose'),
        #         ('/output/cmd_vel', '/turtlesim2/turtle1/cmd_vel'),
        #     ]
        # )
    ])