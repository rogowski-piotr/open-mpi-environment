FROM orwel84/ubuntu-16-mpi:latest

WORKDIR /workspace

RUN apt-get clean \
    && apt-get update \
    && apt-get install openssh-server openssh-client net-tools sudo dnsutils -y \
    && useradd client \
    && echo 'root:root' | chpasswd \
    && sed -i 's/#\?PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config

ENTRYPOINT service ssh restart && bash