from django.shortcuts import render
from .models import Sample
from .models import Calibration
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


def list_calibrations(request):
    calibrations = Calibration.objects.all().order_by('-date')
    return render(request, "samples/calibration/list.html", {
        'calibrations': calibrations,
    })

