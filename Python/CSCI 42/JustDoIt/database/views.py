from django.shortcuts import render, redirect
from .models import Note, Photo
from .forms import *
from django.http import HttpResponse, HttpResponseRedirect

# Create your views here.

def homepage(request):
    return render(request, 'homepage.html')

def home(request):
    all_notes = Note.objects.all
    return render(request, 'index.html', {'all':all_notes})

def notes(request):
    return render(request, 'noteui.html')

def notes2(request):
    return render(request, 'Notes_template_draft.html')

def spotify(request):
    return render(request, 'widget.html')

def notehome(request):
    if request.method == 'POST':
        form = NoteForm(request.POST, request.FILES)

        if form.is_valid():
            form.save()
            Notes = Note.objects.all()
            return HttpResponseRedirect('/notesuccess/')
    else:
        form = NoteForm()

    if request.method == 'GET':
        Notes = Note.objects.all()
        return render(request, 'notehome.html', {'form': form, 'notes' : Notes})
    
    return render(request, 'notehome.html', {'form': form})

def gallery(request): 
  
    if request.method == 'POST': 
        form = PhotoForm(request.POST, request.FILES) 
  
        if form.is_valid(): 
            form.save()
            Photos = Photo.objects.all()
            return HttpResponseRedirect('/success/')
    else: 
        form = PhotoForm() 

    if request.method == 'GET':
        Photos = Photo.objects.all()
        return render(request, 'gallery.html', {'form': form, 'photos': Photos}) 

    return render(request, 'gallery.html', {'form' : form}) 

def success(request):
    return HttpResponseRedirect('/gallery/')

def notesuccess(request):
    return HttpResponseRedirect('/notehome/')

def plain_text_view(request):
    file = open('media/notes/test.txt')
    content = file.read()
    file.close()
    return HttpResponse(content, content_type='text/plain')