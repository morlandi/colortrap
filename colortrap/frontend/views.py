import datetime
from django.shortcuts import render
from django.http import HttpResponse


def homepage(request):
    return render(request, "home.html", {
        'date': datetime.datetime.now()
    })


def contacts(request):
    return HttpResponse("""
<h1>Contacts</h1>...
<a href="/">Home</a>
""")

