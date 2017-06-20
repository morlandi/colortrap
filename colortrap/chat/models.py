from django.db import models


class Message(models.Model):
    date = models.DateTimeField(auto_now_add=True)
    subject = models.CharField(max_length=256, null=False, blank=True)
    body = models.TextField(null=False, blank=True)
