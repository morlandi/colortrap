#!/bin/bash
ansible-playbook -v -i hosts --limit brainstorm.it quick_update.yml --user=brainweb -k
