#!/bin/bash

if [ $# -ne 1 ]
then
    echo "Usage: $0 LEFT_TEXT" >&2
fi
LEFT_TEXT=$1

CURRENT=$(find obj -type f | wc -l)
TOTAL=$(find src -type f | wc -l)
PERCENTAGE=$(bc <<< "scale=0; 100 * $CURRENT / $TOTAL")

TERMINAL_LEN=$(tput cols)
BAR_LEN=$(bc <<< "scale=0; $TERMINAL_LEN * 36 / 100");
LEFT_TEXT_LEN=$(echo -n "$LEFT_TEXT" | wc -m)
PERCENTAGE_LEN=$(echo -n "$PERCENTAGE" | wc -m)
SPACE=$((TERMINAL_LEN - LEFT_TEXT_LEN - PERCENTAGE_LEN - BAR_LEN - 4))

FULL=$(bc <<< "scale=0; $BAR_LEN * $CURRENT / $TOTAL")
EMPTY=$(($BAR_LEN - $FULL))

printf "\r\e[J$LEFT_TEXT"
printf "%${SPACE}s"
printf "%d%% [" $PERCENTAGE
printf "%${FULL}s" | tr ' ' '#'
printf "%${EMPTY}s" | tr ' ' '-'
printf "\e[0m]"
if [ $PERCENTAGE -eq 100 ]
then
    printf "\n"
fi
