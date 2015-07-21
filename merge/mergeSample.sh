#!/bin/bash

INDIR=$1
OUTDIR=$2
NAME=$3

echo "Start Merge $NAME"

./yodamerge -o $OUTDIR/$NAME.yoda $INDIR/BTAG_JET_TRACK_SEL_*.yoda

echo "End Merge $NAME"
