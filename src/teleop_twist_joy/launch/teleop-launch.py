import os

from ament_index_python.packages import get_package_share_directory

import launch
import launch_ros.actions


def generate_launch_description():

    return launch.LaunchDescription([

        launch_ros.actions.Node(
            package='joy', node_executable='joy_node', name='joy_node',
        ),
        launch_ros.actions.Node(
            package='teleop_twist_joy', node_executable='teleop_node',
            name='teleop_twist_joy_node',
            ),
    ])
