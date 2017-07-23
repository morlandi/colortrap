from django.shortcuts import render
from .models import Sample
from django.views.decorators.csrf import csrf_exempt
#Create your views here.

@csrf_exempt
def index(request):

    if request.method == 'POST':

        value = request.POST['value']
        Sample.objects.create(
            value=value,
        )

    else:
        pass

    return render(request, "samples/index.html", {
        'samples': Sample.objects.all().order_by('-date'),


    })
