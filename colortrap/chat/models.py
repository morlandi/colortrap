import uuid
from django.db import models


class Message(models.Model):
    id = models.UUIDField(default=uuid.uuid4, primary_key=True, unique=True, null=False, blank=False, editable=False)
    date = models.DateTimeField(auto_now_add=True)
    subject = models.CharField(max_length=256, null=False, blank=True)
    body = models.TextField(null=False, blank=True)
