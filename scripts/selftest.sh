#!/bin/bash

if [ $1 == '--gui' ]; then
	cmd=xboard
	shift;
else
	cmd="xvfb-run -a xboard -noGUI"
fi

N=$1
ARG1=$2
ARG2=$3
shift 3

if ! [ -d logs ]; then
	mkdir logs
	echo 0 > logs/.seq
	seq=0000
else
	seq=$(($(cat logs/.seq) + 1))
	echo $seq > logs/.seq
	seq=$(printf "%04d" $seq)
fi

FILE=logs/LOG_$seq

i=0
th=0
maxth=$(getconf _NPROCESSORS_ONLN)
while [ $i -lt $N ]; do
	if [ $th -ge $maxth ]; then
		wait -n
		th=$((th-1))
	fi

	th=$((th+1))
	i=$((i+1))
	if [ "$((i%2))" == 0 ]; then
		PLAYER1="$ARG1"
		PLAYER2="$ARG2"
	else
		PLAYER1="$ARG2"
		PLAYER2="$ARG1"
	fi

	$cmd -xexit -mg 1 -tc 4 -mps 40 \
		-fcp "$PLAYER1" -scp "$PLAYER2" -sgf "$FILE" \
		-discourageOwnBooks true -usePolyglotBook true \
		-xmovesound \
		-polyglotBook $(pwd)/scripts/test_book.bin -fNoOwnBookUCI \
		-sNoOwnBookUCI "$@" &
done
wait
