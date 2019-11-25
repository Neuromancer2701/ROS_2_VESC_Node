^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Changelog for package teleop_twist_joy
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

2.2.2 (2019-10-23)
------------------
* Export interfaces for Shared Lib on Windows.
* Make teleop_twist_joy composable.
* Reenable cppcheck.
* Rename teleop_twist_joy.h to teleop_twist_joy.hpp
* Get some basic tests running (`#10 <https://github.com/ros2/teleop_twist_joy/issues/10>`_)
* Port config and launch to ROS 2 (`#11 <https://github.com/ros2/teleop_twist_joy/issues/11>`_)
* Contributors: Chris Lalancette, Scott K Logan, seanyen

2.2.0 (2019-05-31)
------------------
* Fix parameters so things actually work in Dashing. (`#9 <https://github.com/ros2/teleop_twist_joy/issues/9>`_)
* Contributors: Chris Lalancette

2.1.1 (2019-02-08)
------------------
* Add in the ability to control via parameters (`#8 <https://github.com/ros2/teleop_twist_joy/issues/8>`_)
* Contributors: Chris Lalancette

2.1.0 (2018-06-26)
------------------
* ParameterService auto started (`#7 <https://github.com/ros2/teleop_twist_joy/issues/7>`_)
* Contributors: Shane Loretz

2.0.0 (2017-12-08)
------------------
* Initial port to ROS2
* Contributors: Chris Lalancette, Mikael Arguedas, Deanna Hood

0.1.2 (2016-08-31)
------------------
* Fixed incorrect key. (`#21 <https://github.com/ros-teleop/teleop_twist_joy/issues/21>`_)
* Allow custom config file from location outside of this package
* Setting scale_angular_turbo if axis_angular is set so that turning works when turbo is pressed.
* Added turbo scale for angular velocities and accompanying test.
* Add LICENSE.txt.
* Contributors: Daniel Aden, Isaac I.Y. Saito, Mike Purvis, Tony Baltovski

0.1.1 (2015-06-27)
------------------
* Add rostests.
* Added maps to allow multi-dof velocity publishing.
* Added Xbox 360 controller example.
* Contributors: Mike Purvis, Tony Baltovski

0.1.0 (2014-07-25)
------------------
* Added configurations for Logitech Attack3 and Extreme 3D Pro joysticks.
* Initial version, with example config for PS3 joystick.
* Contributors: Mike Purvis, Tony Baltovski
