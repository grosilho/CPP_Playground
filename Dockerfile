FROM ubuntu:latest

USER root

ENV PATH="/root/miniconda3/bin:${PATH}"
ENV CCACHE_DIR="/src/.ccache-docker"
ENV CCACHE_COMPRESS="true"
ENV CCACHE_COMPRESSLEVEL="5"
ENV CCACHE_MAXSIZE="1000M"

RUN apt-get -qq update && \
    apt-get -y upgrade
RUN apt install -y wget

RUN mkdir -p ~/miniconda3
RUN wget https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh -O ~/miniconda3/miniconda.sh
RUN bash ~/miniconda3/miniconda.sh -b -u -p ~/miniconda3
RUN rm ~/miniconda3/miniconda.sh

RUN conda create -y -n cpp
RUN conda run -n cpp conda install -y -c conda-forge git cmake>=3.30.5 gcc>=14.2.0 gxx>=14.2.0 ninja>=1.12.1 ccache doxygen clang-format cmake-format jinja2 lcov python pip

WORKDIR /src
