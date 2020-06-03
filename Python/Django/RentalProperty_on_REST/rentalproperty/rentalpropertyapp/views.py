from django.views.decorators.csrf import ensure_csrf_cookie
from rest_framework import viewsets
from .serializers import RentingItemSerializer
from .models import RentingItem
from django.shortcuts import render

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
    return render(request, 'home.html')