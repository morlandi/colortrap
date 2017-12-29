from django.contrib import admin
from .models import Calibration
from .models import Sample


@admin.register(Calibration)
class CalibrationAdmin(admin.ModelAdmin):
    pass


@admin.register(Sample)
class SampleAdmin(admin.ModelAdmin):
    list_display = ['date', 'value', 'calibration', 'position', ]
    list_editable = ['value', 'calibration', 'position', ]
    date_hierarchy = 'date'
