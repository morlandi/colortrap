#!/bin/bash
source {{django.virtualenv}}/bin/activate
#export DJANGO_SETTINGS_MODULE={{project}}.settings.local_server
cd {{django.root}}/{{project}}
echo 'PYTHON:' `which python`
#echo 'SETTINGS:' $DJANGO_SETTINGS_MODULE
