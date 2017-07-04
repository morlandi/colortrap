from django.conf.urls import url
from .views import homepage
from .views import contacts
from .views import about
from .views import uuid

urlpatterns = [
    url(r'^$', homepage),
    url(r'^contacts/$', contacts),
    url(r'^about/$', about),
    url(r'^uuid/$', uuid),
]
