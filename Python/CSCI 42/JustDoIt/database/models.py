from django.db import models

# Create your models here.
class Note(models.Model):
    note = models.FileField(upload_to='notes/')
    
    def __str__(self):
        return self.note.url

class Photo(models.Model):
    #name = models.CharField(max_length=50)
    photo = models.ImageField(upload_to='images/')

    def __str__(self):
        return self.photo.url