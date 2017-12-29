from django.conf.urls import url
from .views import index
from .views import list_calibrations

urlpatterns = [
    #url(r'^$', homepage),
    url(r'^$', index),
    url(r'^calibrations/$', list_calibrations),
]
