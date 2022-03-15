MPICC=mpicc
CFLAGS=-O2
LIBS=-lm

ifeq (run,$(firstword $(MAKECMDGOALS)))
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  $(eval $(RUN_ARGS):;@:)
endif


main: mpi.c
	${MPICC} ${CFLAGS} $< -o mpi ${LIBS}

run:
	mpirun --allow-run-as-root -np 4 -hostfile hosts.txt ./mpi $(RUN_ARGS)

clean:
	rm mpi