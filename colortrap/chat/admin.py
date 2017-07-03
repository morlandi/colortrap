from django.contrib import admin
from .models import Message


@admin.register(Message)
class MessageAdmin(admin.ModelAdmin):

    list_display = ['date', 'subject', 'body', ]
    date_hierarchy = 'date'
