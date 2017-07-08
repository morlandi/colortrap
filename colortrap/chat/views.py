from django.shortcuts import render
from .models import Message
from django.views.decorators.csrf import csrf_exempt

# Create your views here.

@csrf_exempt
def index(request):

    if request.method == 'POST':
    	subject = request.POST['subject']
    	body = request.POST['body']

    	Message.objects.create(
    		subject=subject,
    		body=body,
    	)

    else:
    	pass

    return render(request, "chat/index.html", {
    	'messages': Message.objects.all().order_by('-date'),
    })
