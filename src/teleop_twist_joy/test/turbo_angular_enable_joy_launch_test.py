import launch
import launch_ros
import launch_ros.actions

import pytest

import test_joy_twist


@pytest.mark.rostest
def generate_test_description(ready_fn):
    teleop_node = launch_ros.actions.Node(
        package='teleop_twist_joy',
        node_executable='teleop_node',
        parameters=[{
            'axis_linear.x': 1,
            'axis_angular.yaw': 0,
            'scale_linear.x': 1.0,
            'scale_linear_turbo.x': 2.0,
            'scale_angular.yaw': 1.0,
            'scale_angular_turbo.yaw': 2.0,
            'enable_button': 0,
            'enable_turbo_button': 1,
        }],
    )

    return (
        launch.LaunchDescription([
            teleop_node,
            launch.actions.OpaqueFunction(function=lambda context: ready_fn()),
        ]), locals()
    )


class TurboAngularEnableJoy(test_joy_twist.TestJoyTwist):

    def setUp(self):
        super().setUp()
        self.joy_msg['axes'] = [0.3, 0.4]
        self.joy_msg['buttons'] = [1, 1]
        self.expect_cmd_vel['linear']['x'] = 0.8
        self.expect_cmd_vel['angular']['z'] = 0.6
