#!/bin/bash
#source {{django.pythonpath}}/activate
#cd {{django.website_home}}
gunicorn {{project}}.wsgi -c gunicorn_{{project}}.conf.py
