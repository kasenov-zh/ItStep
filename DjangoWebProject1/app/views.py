"""
Definition of views.
"""

from datetime import datetime
from django.shortcuts import render
from django.http import HttpRequest

def home(request):
    """Renders the home page."""
    assert isinstance(request, HttpRequest)
    return render(
        request,
        'app/index.html',
        {
            'title':'Home Page',
            'year':datetime.now().year,
        }
    )

def contact(request):
    """Renders the contact page."""
    assert isinstance(request, HttpRequest)
    return render(
        request,
        'app/contact.html',
        {
            'title':'Contact',
            'message':'Your contact page.',
            'year':datetime.now().year,
        }
    )

def about(request):
    """Renders the about page."""
    assert isinstance(request, HttpRequest)
    return render(
        request,
        'app/about.html',
        {
            'title':'About',
            'message':'Your application description page.',
            'year':datetime.now().year,
        }
    )

def new(req : HttpRequest):
    assert isinstance(req, HttpRequest)

    #idVal = req.GET.get('id', None)
    #Filt  = req.GET.get('f', None)
    #if idVal is not None:
    #  from .models import Student
    #  st = Student.objects.get(pk = int(idVal))
    #  st.Name
      

    #  admin.site._registry

    #req.GET['id']
    return render(
        req,
        'app/new1.html',
        {
          'data_link' : '.?q=1?w=2',
          'title':'About',
          'message':'Your application description page.',
          'year':datetime.now().year,
        }
    )
