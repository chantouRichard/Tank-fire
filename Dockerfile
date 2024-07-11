# 使用官方的 Ubuntu 20.04 作为基础镜像
FROM ubuntu:20.04

# 设置环境变量以避免在安装软件包时出现交互提示
ENV DEBIAN_FRONTEND=noninteractive
ENV QT_QPA_PLATFORM=offscreen

# 安装必要的软件包，包括 Qt 和常见的依赖项
RUN apt-get update && \
    apt-get install -y \
    build-essential \
    qt5-default \
    qt5-qmake \
    qtbase5-dev \
    qtmultimedia5-dev \
    gstreamer1.0-plugins-base \
    gstreamer1.0-plugins-good \
    gstreamer1.0-plugins-bad \
    gstreamer1.0-plugins-ugly \
    gstreamer1.0-libav \
    gstreamer1.0-tools \
    gstreamer1.0-x \
    gstreamer1.0-alsa \
    gstreamer1.0-pulseaudio \
    gdb \
    git \
    locales \
    wget \
    && rm -rf /var/lib/apt/lists/*

# 设置 UTF-8 locale
RUN locale-gen en_US.UTF-8
ENV LANG en_US.UTF-8
ENV LANGUAGE en_US:en
ENV LC_ALL en_US.UTF-8

# 设置工作目录
WORKDIR /app

# 复制项目文件到容器中
COPY . /app

# 使用 qmake 和 make 构建项目
RUN qmake -o Makefile tank_fire.pro 
RUN make

# 确保可执行文件具有执行权限
RUN chmod +x /app/tank_fire

# 暂时不需要入口点和 CMD 指令，因为我们只是构建镜像
EXPOSE 80
CMD ["/app/tank_fire"]
