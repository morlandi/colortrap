from {{project}}.settings.settings import *


DEBUG = False
#TEMPLATES[0]['OPTIONS']['debug'] = True
ALLOWED_HOSTS = []
if not DEBUG:
    ALLOWED_HOSTS = ['*', ]

DATABASES = {
   'default': {
       'ENGINE': 'django.db.backends.postgresql_psycopg2',
       'HOST': 'localhost',
       'NAME': '{{database.db_name}}',
       'USER': '{{database.db_user}}',
       'PASSWORD': '{{database.db_password}}',
   }
}

SECRET_KEY = '{{django.secret_key}}'
SESSION_COOKIE_NAME = '{{django.session_cookie_name}}'
SITE_NAME = '{{django.site_name}}'
SERVER_EMAIL = '{{django.server_email}}'
ADMINS = (
    {% for row in django.admins %}
        ('{{row.0}}', '{{row.1}}'),
    {% endfor %}
)
MANAGERS = ADMINS

# Default email
DEFAULT_FROM_EMAIL = '{{django.default_from_email}}'
EMAIL_SUBJECT_PREFIX = '{{django.email_subject_prefix}}'


## "dumb" python SMTP server:
## python -m smtpd -n -c DebuggingServer localhost:1025
#EMAIL_HOST = 'localhost'
#EMAIL_PORT = 1025

# discard email messages
#EMAIL_BACKEND = 'django.core.mail.backends.dummy.EmailBackend'

try:
    from smtp_local_settings import *
except:
    pass
