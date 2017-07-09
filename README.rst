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

POST a new sample via Telnet
----------------------------

$ telnet 127.0.0.1 8000
POST /samples/ HTTP/1.0
Content-Type: application/x-www-form-urlencoded
Content-Length: 11

value=122.3

References
----------

- `How are parameters sent in an HTTP POST request? <https://stackoverflow.com/questions/14551194/how-are-parameters-sent-in-an-http-post-request#14551219>`_

