"""JustDoIt URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/1.11/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  url(r'^$', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  url(r'^$', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.conf.urls import url, include
    2. Add a URL to urlpatterns:  url(r'^blog/', include('blog.urls'))
"""
from django.conf.urls import url, include
from database import views

urlpatterns = [
    url(r'^notes/', views.notes, name='notes'),
    url(r'^notes2/', views.notes2, name='notes2'),
    url(r'^spotify/', views.spotify, name='spotify'),
    url(r'^homepage/', views.homepage, name='homepage'),
    url(r'^gallery/', views.gallery, name='gallery'),
    url(r'^success/', views.success, name='success'),
    url(r'^notehome/', views.notehome, name='notehome'),
    url(r'^notesuccess/', views.notesuccess, name='notesuccess'),
    url(r'^plain_text_view/', views.plain_text_view, name='plain_text_view')
]