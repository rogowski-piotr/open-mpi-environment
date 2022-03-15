#!/bin/sh

service ssh restart

grep -q $(hostname) '/workspace/hosts.txt' || bash -c "echo $(hostname) >> /workspace/hosts.txt"

sleep infinity