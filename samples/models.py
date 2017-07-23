from django.db import models
import uuid
# Create your models here.
class Sample(models.Model):
    id = models.UUIDField(default=uuid.uuid4, primary_key=True, unique=True, null=False, blank=False, editable=False)
    date = models.DateTimeField(auto_now_add=True)
    #value = models.FloatField(default=0.0)
    value = models.CharField(max_length=16, null=False, blank=True)
