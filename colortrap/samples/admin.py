from django.contrib import admin
from .models import Sample
# Register your models here.
@admin.register(Sample)
class SampleAdmin(admin.ModelAdmin):

	list_display = ['date', 'value', ]
	date_hierarchy = 'date'