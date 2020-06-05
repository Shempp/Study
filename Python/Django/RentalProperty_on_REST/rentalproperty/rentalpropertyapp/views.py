from django.http import HttpResponseRedirect
from django.urls import reverse
from django.views.decorators.csrf import ensure_csrf_cookie
from django.contrib.auth import authenticate
from django.contrib.auth import login as login_user
from django.shortcuts import render
from django.contrib.auth import logout as logout_user
from django.contrib.auth.decorators import login_required
from rest_framework import viewsets
from .serializers import RentingItemSerializer
from .models import RentingItem
from .forms import LoginForm

# Create your views here.

class RentingItemViewSet(viewsets.ModelViewSet):
    """
    API endpoint that allows users to be viewed or edited.
    """
    queryset = RentingItem.objects.all().order_by('id')
    serializer_class = RentingItemSerializer

# This decorator forces the submit to send a CSRF cookie.
@ensure_csrf_cookie
def home(request):
    # If not authenticated - redirect to login page
    if not request.user.is_authenticated:
        return HttpResponseRedirect(reverse('rentalpropertyapp:rentalproperty-login'))

    return render(request, 'home.html')

def login(request):
    if request.method == 'POST':
        login_form_request = LoginForm(request.POST)
        if login_form_request.is_valid():
            login = login_form_request.cleaned_data['login']
            password = login_form_request.cleaned_data['password']
            user = authenticate(username=login, password=password)
            if user:
                login_user(request, user)
                return HttpResponseRedirect(reverse('rentalpropertyapp:rentalproperty-home'))

    login_form_default = LoginForm()
    return render(request, 'login.html', {'login_form': login_form_default})


@login_required
def logout(request):
    logout_user(request)
    return HttpResponseRedirect(reverse('rentalpropertyapp:rentalproperty-login'))