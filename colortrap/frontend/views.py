import datetime
from django.shortcuts import render
from django.http import HttpResponse


def homepage(request):
    return render(request, "home.html", {
        'date': datetime.datetime.now()
    })


def contacts(request):
    return render(request, "contacts.html", {
    })

def about(request):
    return render(request, "about.html", {
    })

