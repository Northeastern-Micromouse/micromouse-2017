#Build Process:

This jank build process will proceed in two stages: host stage and guest stage.
Host stage commands are all issued on your computer, in the top level
micromouse directory. This stage will be used to prepare all files for use on
the beagle. The guest stage commands will be issued on the beagle via SSH or
serial, and will be used to place all prepared files in their intended
destinations.

#Dev Process:

If you develop a new feature, please ensure that you update the build process
to reflect your new change. The current, up to date, process follows below:

##Host Stage:

1) run install.sh

##Guest Stage:

1) run board_setup.sh
