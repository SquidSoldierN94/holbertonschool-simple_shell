#!/bin/bash

if [ -f /proc/sys/kernel/pid_max ]; then
    max_pid=$(cat /proc/sys/kernel/pid_max)
    echo "Maximum process ID: $max_pid"
else
    echo "Unable to determine maximum process ID"
fi

