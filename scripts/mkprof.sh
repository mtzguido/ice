#!/bin/bash

set -ue

N=${1:-10}

./chess --moves $N

gprof chess gmon.out > profile

gprof2dot.py profile > vprof