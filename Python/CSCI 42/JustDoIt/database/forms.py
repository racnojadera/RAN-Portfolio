from django import forms
from .models import *

class PhotoForm(forms.ModelForm):

    class Meta:
        model = Photo
        fields = ['photo']


class NoteForm(forms.ModelForm):
    
    class Meta:
        model = Note
        fields = ['note']