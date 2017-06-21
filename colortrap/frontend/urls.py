from django.conf.urls import url
from .views import homepage
from .views import contacts

urlpatterns = [
    url(r'^$', homepage),
    url(r'^contacts/$', contacts),
]
