FROM ros:kinetic-ros-base-xenial

MAINTAINER Lander Usategui <lander@aliasrobotics.com>

COPY scenario6-local /root/ros_catkin_ws/src/scenario6

RUN apt update && apt install -y software-properties-common \
  && add-apt-repository -y ppa:deadsnakes/ppa \
  && apt update && apt install -y python3.7 python3.7-dev python3-pip libssl-dev libffi-dev \
  libxml2-dev libxslt1-dev zlib1g-dev libgmp3-dev gengetopt libpcap-dev flex byacc libjson-c-dev libunistring-dev \
  && rm -rf /var/lib/apt/lists/*

RUN /bin/bash -c "cd /root/ros_catkin_ws \
  && source /opt/ros/kinetic/setup.bash \
  && catkin_make_isolated --install --install-space /opt/ros/kinetic \
  && cd && rm -r /root/ros_catkin_ws"

RUN python3.7 -m pip install --upgrade pip setuptools wheel

RUN pip3.7 install aztarna

COPY launch_script.bash /root/

COPY motd /etc/motd

RUN echo "cat /etc/motd" >> /root/.bashrc

ENTRYPOINT ["/root/launch_script.bash"]
