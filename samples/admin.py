from django.contrib import admin
from .models import Sample


@admin.register(Sample)
class SampleAdmin(admin.ModelAdmin):
    list_display = ['date', 'value', 'calibration', 'position', ]
    list_editable = ['value', 'calibration', 'position', ]
    date_hierarchy = 'date'
