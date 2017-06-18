Colortrap
=========

more to write here ...

Manual setup
------------

.. code:: bash

    mkvirtualenv --python=/usr/local/bin/python3 colortrap
    pip install -r requirements.txt

    python manage.py migrate
    python manage.py createsuperuser
    	... admin + password

Run development web server
--------------------------

.. code:: bash

    workon colortrap
    cd colortrap
    python manage.py runserver

    http://127.0.0.1:8000/ or, ...
    http://127.0.0.1:8000/admin/ ...    
