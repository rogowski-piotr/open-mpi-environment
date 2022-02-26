FROM orwel84/ubuntu-16-mpi:latest

WORKDIR /workspace

RUN apt-get clean \
    && apt-get update \
    && apt-get install openssh-server openssh-client net-tools sudo dnsutils -y \
    && echo 'root:root' | chpasswd \
    && sed -i 's/#\?PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config \
    && ssh-keygen -q -t rsa -N '' -f /root/.ssh/id_rsa \
    && chmod go-w /root/ \
	&& chmod 700 /root/.ssh \
	&& chown root /root \
	&& chown root /root/.ssh

ENTRYPOINT service ssh restart && bash