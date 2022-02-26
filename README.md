### Quick Start

*if you are working on windows run in Git Bash first:
```shell script
dos2unix entrypoint.sh
```

#### 1. Run Docker compose
```shell script
docker-compose up --build -d
```

#### 2. Enter into one of the containers
```shell script
docker exec -it mpi-node-1 /bin/bash
```

#### 3. Exchange keys between containers for ssh communication
*confirm: yes and type password: root
```shell script
ssh-copy-id root@mpi-node-1 \
	&& ssh-copy-id root@mpi-node-2 \
	&& ssh-copy-id root@mpi-node-3
```

#### 4. Ensure that host.txt contains only unique elements

#### 5. Compile the program
```shell script
mpicc example.c -o example
```

#### 6. Run
```shell script
mpirun -hostfile hosts.txt -np 4 --allow-run-as-root example
```