Colortrap
=========

more to write here ...

Manual setup
------------

.. code:: bash

    mkvirtualenv --python=/usr/local/bin/python3 colortrap
    pip install -r requirements.txt
    python manage.py createsuperuser
    	... admin + password

Run development web server
--------------------------

.. code:: bash

    workon colortrap
    cd colortrap
    python manage.py migrate
    python manage.py runserver

    http://127.0.0.1:8000/ or, ...
    http://127.0.0.1:8000/admin/ ...


Send_Color sketch notes and connections
=======================================

Groove Color Sensor cables
--------------------------

    - SCL: yellow
    - SDA: green
    - VCC: red
    - GND: black

Arduino connections
-------------------

esp8266 debug port:

    - TX with RX Arduino line (pin 2)
    - RX with TX Arduino line (pin 3)
    - GND
    - 3V3

groove color sensor:

    - SCL: analog input A5
    - SDA: analog input A4
    - VCC: 5V
    - GND: GND

red led:

    - pullup input D13

press button:

    - connect D12 to GND to press

Led codes
---------

- During setup: led ON
- Setup complete:
    + 10 blinks if wi-fi connection is available
    + 2 blinks in case of error
- New acquisition:
    + 1 blink after button press
    + 1 blink after color read
    + 5 blinks after sample transmission (success)
    + 2 blinks after sample transmission (failure)
