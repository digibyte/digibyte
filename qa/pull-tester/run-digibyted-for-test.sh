#!/bin/bash
DATADIR="/home/scott/Desktop/digibyte/.digibyte"
rm -rf "$DATADIR"
mkdir -p "$DATADIR"/regtest
touch "$DATADIR/regtest/debug.log"
tail -q -n 1 -F "$DATADIR/regtest/debug.log" | grep -m 1 -q "Done loading" &
WAITER=$!
PORT=`expr $BASHPID + 10000`
"/home/scott/Desktop/digibyte/src/digibyted" -connect=0.0.0.0 -datadir="$DATADIR" -rpcuser=user -rpcpassword=pass -listen -keypool=3 -debug -debug=net -logtimestamps -port=$PORT -regtest -rpcport=`expr $PORT + 1` &
DIGIBYTED=$!

#Install a watchdog.
(sleep 10 && kill -0 $WAITER 2>/dev/null && kill -9 $DIGIBYTED $$)&
wait $WAITER

if [ -n "$TIMEOUT" ]; then
  timeout "$TIMEOUT"s "$@" $PORT
  RETURN=$?
else
  "$@" $PORT
  RETURN=$?
fi

(sleep 15 && kill -0 $DIGIBYTED 2>/dev/null && kill -9 $DIGIBYTED $$)&
kill $DIGIBYTED && wait $DIGIBYTED

# timeout returns 124 on timeout, otherwise the return value of the child
exit $RETURN
