#!/bin/bash
kill -9 `ps aux | grep {{django.pythonpath}} | grep -v grep | awk '{ print $2 }'`
