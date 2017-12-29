from django.db import models
import uuid
from django.utils.encoding import python_2_unicode_compatible


@python_2_unicode_compatible
class Calibration(models.Model):
    id = models.UUIDField(default=uuid.uuid4, primary_key=True, unique=True, null=False, blank=False, editable=False)
    date = models.DateTimeField(auto_now_add=True)
    description = models.CharField(max_length=64, null=False, blank=True)
    notes = models.TextField(null=False, blank=True)

    def __str__(self):
        return self.description

# Create your models here.
class Sample(models.Model):
    id = models.UUIDField(default=uuid.uuid4, primary_key=True, unique=True, null=False, blank=False, editable=False)
    date = models.DateTimeField(auto_now_add=True)
    #value = models.FloatField(default=0.0)
    value = models.CharField(max_length=16, null=False, blank=True)
    calibration = models.ForeignKey(Calibration, null=True, blank=True)
    position = models.IntegerField(null=True, blank=True)
