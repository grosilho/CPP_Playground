FROM ubuntu:latest
USER root
RUN apt-get -qq update && \
    apt-get -y upgrade
RUN apt install -y git 
RUN apt install -y build-essential 
RUN apt install -y ccache
RUN apt install -y cmake
RUN apt install -y doxygen
RUN apt install -y ninja-build
RUN apt install -y python3
RUN apt install -y cmake-format clang-format
WORKDIR /src
